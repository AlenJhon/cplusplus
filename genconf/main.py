#!/usr/bin/env python
#coding:utf-8
import json
import os
from jinja2 import Environment, ChoiceLoader, FileSystemLoader, Template

jenv=Environment(loader=ChoiceLoader([FileSystemLoader('./'), FileSystemLoader('tpl')]))

def get_promtail_conf(f):
    argv={}
    with open(f, 'r') as pf:
        argv = json.load(pf)
    
    if argv.get("promtail") is None:
        print("conf json:{} don't promtail key".format(f))
        return
    cluster = argv["cluster"]
    
    ret_conf = argv["promtail"]
    idx=1
    job_lists = ret_conf.get("job_lists")
    if job_lists is None:
        print("conf json:{} don't job_lists key".format(f))
        return
    for x in job_lists:
        world = x["world"]
        x["job_name"]=x["job_name"].format(idx=idx)
        idx += 1
        x["job"]=x["job"].format(cluster=cluster,world=world)
        x["path"]=x["path"].format(cluster=cluster,world=world)
    return ret_conf


def render_file(srcfile, dstfile, env):
    tpl = jenv.get_template(srcfile)
    ct = tpl.render(**env)
    try:
        ctt=Template(ct).render(**env)
    except Exception as e:
        print("render again fail")
        ctt = ct
    if not os.path.exists(os.path.dirname(dstfile)):
        os.makedirs(os.path.dirname(dstfile))
    open(dstfile,'wb').write(ctt.encode("utf-8"))


def main():
    conf = get_promtail_conf("./argv/dev.json")
    render_file("./tpl/promtail.tpl", "./promtail.yaml", conf)

if __name__ == "__main__":
    main()