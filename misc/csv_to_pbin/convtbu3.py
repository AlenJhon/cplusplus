#coding=utf-8

import tornado.ioloop
import tornado.web
# import tornado.httpclient
import shutil
import os
import sys
import traceback
import json
import subprocess
import datetime
from config import settings
from csv2pbin import csv_to_pbin

##############################################
UPLOAD_FILENAME="target_tables"
GAME_PROTO="game_proto"

CODE_RUN_OK=(0, "CONV FINISH ")
ERR_CODE_RUN_EXCEPTION=(-1, "<捕获到异常>")
ERR_CODE_GAME_PROTO_NOT_EXISTS=(-100,   "<协议文件不存在>")
ERR_CODE_UPDATE_SHARE_FAILED=(-101, "<更新协议文件出错啦>")



def check_and_create_dir(_path):
    if not os.path.exists(_path):
        os.makedirs(_path)

LOG_ERROR='error'
LOG_OK='OK'
LOG_INFO='info'

g_resp_webc = []
g_resp_index = 1
g_from_webc = False
def write_to_webc(h, d, lv, fin):
    print("write_to_webc",d)
    global g_resp_index
    global g_resp_webc
    
    _status = "INFO"
    _idx = g_resp_index
    g_resp_index += 1
    _from = "{}:{}".format(h.request.remote_ip, os.getpid())
    if lv == LOG_ERROR:
        _status = "ERROR"
    elif lv == LOG_OK:
        _status = "SUCCESS"
    
    d = "[%s]"%(datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S")) + d
    g_resp_webc.append({"status":"{}#{}#[{}]".format(_idx,_from,_status), "msg": d})
    
    if fin:
        resp = {'rows': g_resp_webc }
        h.write(json.dumps(resp))
        h.finish()
        g_resp_webc = [] # reset
        g_resp_index = 0
        sys.stdout.flush()


def write_to_web(h, d, log_level=LOG_INFO, isfinish=None, webc=False):
    d += '...'
    if webc:
        write_to_webc(h, d, log_level, isfinish)
        return
    
    if log_level == LOG_INFO:
        bgc = '#909399'
        d = '##:&nbsp' + d + '&nbsp[INFO]'
    elif log_level == LOG_ERROR:
        bgc = '#F56C6C'
        d = '##:&nbsp' + d +'&nbsp[ERROR]'
    elif log_level == LOG_OK:
        bgc = '#67C23A'
        d = '##:&nbsp' + d + '&nbsp[SUCCESS]'
    
    if isfinish:
        bgc = '#409EFF'
    h.write('''<div style="background:{};"><span>[{}]{}</span></div>'''.format(bgc,datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S"), d))

    if isfinish:
        h.finish()
        sys.stdout.flush()
    else:
        h.flush()


def response(h, st, exmsg="", webc=False):
    if webc:
        write_to_web(h, st[1]+exmsg, LOG_OK if st[0]==0 else LOG_ERROR, True, True)
        return
    write_to_web(h, "status: {},&nbsp msg: {}".format(st[0], st[1]+exmsg), isfinish=True)


def make_pbin_path(csv_path):
    # xxDesc.data difference u1
    fname = os.path.basename(csv_path).split('_')[0] + '.data'
    return os.path.join(os.path.dirname(csv_path), fname)

# p4
def run_sys_cmd(cmd):
    if settings['is_show_cmd']:
        print("Rum CMD: [%s] ......" % cmd)
    status, out_put = subprocess.getstatusoutput(cmd)
    if status != 0:
        print("Run CMD: [%s] Error, Msg: [%s]" % (cmd, out_put))
    return status, out_put

def make_p4_cmd(cmd_suffix):
    cmd_prefix = "%s " % (settings['p4_bin_path'])
    return cmd_prefix + cmd_suffix

def P4Login():
    os.environ["P4USER"]=settings['p4user']
    os.environ["P4PASSWD"]=settings['p4pass']
    os.environ["P4PORT"]=settings['p4port']
    os.environ["P4CHARSET"]=settings['p4charset']
    os.environ["P4CLIENT"]=settings['p4client']
    login_cmd="echo %s|%s login" % (settings['p4pass'], settings['p4_bin_path'])
    status, out_put = run_sys_cmd(login_cmd)
    if status != 0:
        raise Exception(out_put)
    return status

def call_p4cmd(cmd):
    fullcmd = make_p4_cmd(cmd)
    if not settings['is_sync_p4']:
        print("Rum CMD: [%s] ......" % fullcmd)
        return
    status, out_put = run_sys_cmd(fullcmd)
    if status != 0:
        raise Exception(out_put)

def call_shellcmd(cmd):
    status, out_put = run_sys_cmd(cmd)
    if status != 0:
        raise Exception(out_put)

def sync_to_p4(p4_root_path, p4_remote_path, src_pbin_path, exmsg):
    call_shellcmd("cd %s"%p4_root_path)

    call_p4cmd('sync -f %s...' % p4_remote_path)

    call_p4cmd('revert %s...' % p4_remote_path)

    for xtb in src_pbin_path:
        pbin_path = p4_remote_path + os.path.basename(xtb)
        call_p4cmd('edit %s' % pbin_path)

        pbin_local_path = p4_root_path + pbin_path
        call_shellcmd('cp %s %s'%(xtb, pbin_local_path))
        
        call_p4cmd('add -f %s' % pbin_path)

        call_p4cmd("submit -f submitunchanged -d \"Client HostInfo: [IP%s]\"" % exmsg)


def cp_list(src_path_list, dest_path):
    check_and_create_dir(dest_path)
    
    for xone in src_path_list:
        rcmd = 'cp %s %s'%(xone, dest_path)
        call_shellcmd(rcmd)


def check_pbin_logic(rescheck_path, tmp_pbin_path, rt_tb, n_rt_tb):
    if not os.path.exists(rescheck_path):
        raise Exception("{} don't exists ".format(rescheck_path))

    rescheck_dirname = os.path.dirname(rescheck_path)
    cmd = 'sudo chgrp -R gsgame %s' % rescheck_dirname
    call_shellcmd(cmd)

    cmd = 'sudo chmod -R g+w %s' % rescheck_dirname
    call_shellcmd(cmd)

    # copy .data to current path
    check_and_create_dir(tmp_pbin_path)
    _cmd = "rm -rf %s/*.data"%(tmp_pbin_path)
    call_shellcmd(_cmd)
    if len(rt_tb) > 0:
        cp_list(rt_tb, tmp_pbin_path)
    if len(n_rt_tb) > 0:
        cp_list(n_rt_tb, tmp_pbin_path)

    log_path = os.path.join(rescheck_dirname, 'log')
    if not os.path.exists(log_path): 
        cmd = 'mkdir -p %s' % log_path 
        call_shellcmd(cmd)
    
    cmd = "rm -rf %s/*.og"%(log_path)
    call_shellcmd(cmd)

    # cmd = "%s -G %s"%(rescheck_path, rescheck_dirname) # ready run jenkins
    # call_shellcmd(cmd)

    cmd = "sed -i 's#<path>LOG_PATH<#<path>%s\/rescheck<#g' %s/rescheck.default.xml" % (log_path, rescheck_dirname)
    call_shellcmd(cmd)

    cmd = "sed -i 's#<dir>RES_PATH<#<dir>%s<#g' %s/rescheck.default.xml" % (tmp_pbin_path, rescheck_dirname)
    call_shellcmd(cmd)

    cmd = "sudo chgrp jenkins %s/rescheck.default.xml"%(rescheck_dirname)
    call_shellcmd(cmd)
    cmd = 'sudo chmod -R g+w %s/rescheck.default.xml' %(rescheck_dirname)
    call_shellcmd(cmd)

    cmd = "cd %s; ./rescheck --config=./rescheck.default.xml --start" % (rescheck_dirname)
    status,out_put = run_sys_cmd(cmd)
    if status != 0:
        old_status = status
        old_cmd = cmd
        old_out_put = out_put
        _cmd = 'cd %s; grep "ERROR" ./log/rescheck.all.log | tail -n20' % (rescheck_dirname)
        status, out_put = run_sys_cmd(_cmd)
        if out_put != "":
            return Exception("{}\n{}\n{}".format(old_cmd, old_status, out_put))
        else:
            return Exception("{}\n{}\n{}".format(old_cmd, old_status, old_out_put))






def proc(req):
    global g_from_webc
    request_from_webc = False
    if req.get_body_argument("webc", None) == "webc":
        request_from_webc = True
    g_from_webc = request_from_webc

    # ./target_tables/u3_main/remote_ip/*.csv
    select_server = req.get_body_argument("select_server")
    print("select_server=", select_server, ",g_from_webc=",g_from_webc)

    write_to_web(req, "服务器已经收到的请求啦, 即将开始转表 ", webc=g_from_webc)
    write_to_web(req, "构建指定服 : %s "%(select_server), webc=g_from_webc)

    csv_path = os.path.join( os.path.dirname(__file__), UPLOAD_FILENAME )
    # print(csv_path)
    
    csv_path = os.path.join(csv_path, select_server);
    check_and_create_dir(csv_path)

    remote_ip = req.request.remote_ip;
    csv_path = os.path.join(csv_path, remote_ip);
    check_and_create_dir(csv_path)
    
    # write local
    if request_from_webc:
        file_metas = req.request.files['file']
    else:
        file_metas = req.request.files['_target_scv_list']
    target_csv_list = []
    for meta in file_metas:
        filename = meta['filename']
        filepath = os.path.join(csv_path, filename)
        target_csv_list.append(filepath)

        with open(filepath, 'wb') as up:
            up.write(meta['body'])
        write_to_web(req, "CSV文件 :  [ {fn} ]  Server Recv OK !".format(fn=filename), webc=g_from_webc)
    
    
    # gen proto
    # update share  default update develop
    # rv = os.system("bash genproto.sh")
    # if rv != 0:
    #     print("genproto failed .")
    #     write_to_web(req, "genproto failed ", LOG_ERROR, webc=g_from_webc)
    #     return response(req, ERR_CODE_UPDATE_SHARE_FAILED, webc=g_from_webc)
    
    runtime_tb = {}
    none_runtime_tb = {}
    for csv_path in target_csv_list:
        write_to_web(req, "开始转表格 [%s] "%( os.path.basename(csv_path)), webc=g_from_webc )

        # conv 
        rv, msg, is_btl_tb = csv_to_pbin(csv_path, make_pbin_path(csv_path), select_server)
        if rv != 0:
            write_to_web(req, msg, LOG_ERROR, webc=g_from_webc)
        else:
            pbin_basename = make_pbin_path(csv_path)
            if is_btl_tb:
                none_runtime_tb[pbin_basename] = True
            else:
                runtime_tb[pbin_basename] = True

            write_to_web(req, "表格 [ {} ] 转 {}.data 完成".format(
                os.path.basename(csv_path), os.path.basename(csv_path).split('_')[0]
            ), LOG_OK, webc=g_from_webc)

    # make pull path
    runtime_tb_fullpath = []
    cwd = os.getcwd()
    if len(runtime_tb) > 0:
        for xtb in runtime_tb:
            runtime_tb_fullpath.append(os.path.join(cwd, xtb))
    none_runtime_tb_fullpath = []
    if len(none_runtime_tb) > 0:
        for xtb in none_runtime_tb:
            none_runtime_tb_fullpath.append(os.path.join(cwd, xtb))

    write_to_web(req, "开始表格逻辑校验 ", webc=g_from_webc)
    # check logic
    res_check_path = "/data/res_u3/{vbranch}/rescheck".format(vbranch=select_server)
    tmp_pbin_path = "/data/res_u3/{vbranch}/curpbin".format(vbranch=select_server)

    check_pbin_logic(res_check_path, tmp_pbin_path, runtime_tb_fullpath, none_runtime_tb_fullpath)
    write_to_web(req, "表格逻辑校验通过 ", webc=g_from_webc)

    write_to_web(req, "开始同步到 p4 ", webc=g_from_webc)
    # sync to p4
    P4Login()

    vbranch_tag = '' if select_server=='u3_main' else select_server
    cwd = os.getcwd()
    if len(runtime_tb) > 0:
        sync_to_p4(settings['p4_local_path_prefix'], settings['p4_remote_pbtable_runtime'].format(vbranch_tag=vbranch_tag), 
            runtime_tb_fullpath, remote_ip)
    
    if len(none_runtime_tb) > 0:
        sync_to_p4(settings['p4_local_path_prefix'],  settings['p4_remote_pbtable_none_runtime'].format(vbranch_tag=vbranch_tag),
            none_runtime_tb_fullpath, remote_ip)
    write_to_web(req, "已经同步到 p4 ", webc=g_from_webc)

    # copy file for sync
    cp_dest_path = os.path.join(settings['p4_sync_base_dir'], select_server, "data")
    check_and_create_dir(cp_dest_path)
    if len(runtime_tb_fullpath) > 0:
        cp_list(runtime_tb_fullpath, cp_dest_path)
    if len(none_runtime_tb_fullpath) > 0:
        cp_list(none_runtime_tb_fullpath, cp_dest_path)

    return response(req, CODE_RUN_OK, webc=g_from_webc)


class conv_file_handler(tornado.web.RequestHandler):
    def initialize(self):
        self.set_default_headers()

    def set_default_headers(self):
        # self.set_header('Access-Control-Allow-Headers', 'Content-Type')
        self.set_header('Access-Control-Allow-Origin', '*') 
        self.set_header('Access-Control-Allow-Headers', 'Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With')
        self.set_header('Access-Control-Allow-Methods', 'DELETE, POST, GET, OPTIONS')

    def get(self):
        self.render('index.html')

    def options(self):
        pass

    def post(self):
        try:
            return proc(self)
        except Exception as e:
            exc_type, exc_value, exc_traceback = sys.exc_info()
            print("*** format_exception:")
            print(traceback.format_exc())
            msg = repr(traceback.format_exception(exc_type, exc_value, exc_traceback))
            write_to_web(self, msg, LOG_ERROR, webc=g_from_webc)
            return response(self, ERR_CODE_RUN_EXCEPTION, webc=g_from_webc)


def init():
    upload_path = os.path.join( os.path.dirname(__file__), UPLOAD_FILENAME )
    if not os.path.exists(upload_path):
        os.mkdir(upload_path)

    game_proto = os.path.join( os.path.dirname(__file__), GAME_PROTO )
    if not os.path.exists(game_proto):
        os.mkdir(game_proto, 777) # for jenkins

if __name__ == '__main__':
    init()

    app = tornado.web.Application([
        (r'/conv', conv_file_handler),
        (r'/', conv_file_handler),
        ])
    lport = settings.get('listen_port', 3000)
    app.listen(lport)
    print("start listen {} ...".format(lport))
    tornado.ioloop.IOLoop.instance().start()
        
