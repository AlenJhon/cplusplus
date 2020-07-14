#coding:utf-8

import sys
import os
import stat
import csv
import json
import traceback
from google.protobuf import text_format

# copy from descriptor.py 
# filed cpptype
CPPTYPE_INT32       = 1
CPPTYPE_INT64       = 2
CPPTYPE_UINT32      = 3
CPPTYPE_UINT64      = 4
CPPTYPE_DOUBLE      = 5
CPPTYPE_FLOAT       = 6
CPPTYPE_BOOL        = 7
CPPTYPE_ENUM        = 8
CPPTYPE_STRING      = 9
CPPTYPE_MESSAGE     = 10
MAX_CPPTYPE         = 10
# field label
LABEL_OPTIONAL      = 1
LABEL_REQUIRED      = 2
LABEL_REPEATED      = 3
MAX_LABEL           = 3
#field type
TYPE_DOUBLE         = 1
TYPE_FLOAT          = 2
TYPE_INT64          = 3
TYPE_UINT64         = 4
TYPE_INT32          = 5
TYPE_FIXED64        = 6
TYPE_FIXED32        = 7
TYPE_BOOL           = 8
TYPE_STRING         = 9
TYPE_GROUP          = 10
TYPE_MESSAGE        = 11
TYPE_BYTES          = 12
TYPE_UINT32         = 13
TYPE_ENUM           = 14
TYPE_SFIXED32       = 15
TYPE_SFIXED64       = 16
TYPE_SINT32         = 17
TYPE_SINT64         = 18
MAX_TYPE            = 18

def is_int_field_type(ft):
    if ft in [3, 4, 5, 6, 7, 8, 13]: #exclude TYPE_ENUM
        return True
    return False

def is_string_field_type(ft):
    if ft in [9]:
        return True
    return False

def get_field_type_name(ft):
    if ft == 1:
        return "TYPE_DOUBLE"
    elif ft == 2:
        return "TYPE_FLOAT"
    elif ft == 3:
        return "TYPE_INT64"
    elif ft == 4:
        return "TYPE_UINT64"
    elif ft == 5:
        return "TYPE_INT32"
    elif ft == 6:
        return "TYPE_FIXED64"
    elif ft == 7:
        return "TYPE_FIXED32"
    elif ft == 8:
        return "TYPE_BOOL"   
    elif ft == 9:
        return "TYPE_STRING"
    elif ft == 10:
        return "TYPE_GROUP"
    elif ft == 11:
        return "TYPE_MESSAGE"
    elif ft == 12:
        return "TYPE_BYTES"   
    elif ft == 13:
        return "TYPE_UINT32"
    elif ft == 14:
        return "TYPE_ENUM"
    elif ft == 15:
        return "TYPE_SFIXED32"
    elif ft == 16:
        return "TYPE_SFIXED64"   
    elif ft == 17:
        return "TYPE_SINT32"
    elif ft == 18:
        return "TYPE_SINT64"
    else:
        return "UNKNOWN"

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        pass
    
    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        pass
    return False

def get_message_name(csv_path):
    return os.path.basename(csv_path).split('_')[0]

def get_message_type(proto_pb, message_name):
    return getattr(proto_pb, message_name, None)

def get_message_descriptor(proto_pb, message_name):
    message_type = get_message_type(proto_pb, message_name)
    if message_type != None:
        return message_type.DESCRIPTOR
    else:
        return None

def field_is_message(field_desc):
    return field_desc.type == 11

def field_is_repeated(field_desc):
    return field_desc.label == 3

# this function copy from pbdc plugins comm.py
def camel_style_name(name):
    rname = ''
    trans = True
    for ch in name:
        if ch == '_':
            trans = True
        else:
            if ch.isupper():
                trans = False
            if ch.islower() and trans:
                rname += ch.upper()
                trans = False
            else:
                rname += ch
    return rname


def get_value_by_cn(enum_json, type_key, cn):
    l_data = enum_json[type_key] # don.t exists throw error 
    for numk in l_data:
        if l_data[numk]['cn'] == cn:
            return int(numk)
    return -1


def conv_enum_name(msg_desc, row_data, enum_json, header_dict, col_name_prefix= ''):
    for field_desc  in msg_desc.fields:
        field_name = field_desc.name
        field_cpptype = field_desc.cpp_type
        field_type = field_desc.type

        if field_is_repeated(field_desc):
            rename = camel_style_name(field_name)
            num_key= rename+'.num'
            if field_is_message(field_desc):
                field_repeat_len = 0 if not row_data[num_key] else int(row_data[num_key])
                row_data[num_key] = field_repeat_len # update to int
                for idx in range(field_repeat_len):
                    conv_enum_name(field_desc.message_type, row_data, enum_json, header_dict, "{field}__{i}.".format(field=rename, i=idx))
            else:
                field_repeat_len = int(row_data[num_key])
                row_data[num_key] = field_repeat_len # update to int
                for idx in range(field_repeat_len):
                    print( row_data[rename+'__{idx}'.format(idx=idx)] )
        else:
            if field_is_message(field_desc):
                conv_enum_name(field_desc.message_type, row_data, enum_json, header_dict, field_name+'.')
            else:
                rename = col_name_prefix + camel_style_name(field_name)
                #conv enum cname to int 
                if field_type == TYPE_ENUM:
                    if is_number(row_data[rename]):
                        # print("rename= {}\t".format(rename),
                        # "row_data[{}]= {}\t".format(rename, row_data[rename]), 
                        # "row_data[{}] is number {}\t".format(rename, is_number(row_data[rename])),
                        # "field_type= {}\t".format(get_field_type_name(field_type)), 
                        # "enum type name= {}".format(header_dict[rename]['typename']) ,
                        # )
                        row_data[rename] = int(row_data[rename])
                    else: # need conv
                        if not row_data[rename]: # default
                            row_data[rename] = 0
                        else:
                            enum_cn = row_data[rename]
                            field_type_name = header_dict[rename]['typename'] # example BattleLevelType
                            conv_res = get_value_by_cn(enum_json, field_type_name, enum_cn)
                            if conv_res < 0:
                                _msg = "field_type_name:{}, cn:{} failed .".format(field_type_name, enum_cn)
                                print(_msg)
                                raise Exception(_msg)
                            row_data[rename] = conv_res # update 
                
                if is_int_field_type(field_type):
                    if not row_data[rename]:
                        row_data[rename] = 0
                    else:
                        row_data[rename] = int(row_data[rename])
                elif is_string_field_type(field_type):
                    if not row_data[rename]:
                        row_data[rename] = ''
    # // end conv_enum_name

def get_csv_head(csv_path):
    csv_head_dict = {}
    row_first = []
    row_second = []
    with open(csv_path, 'r', encoding='gbk') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        head_info_count = 0
        for row in csv_reader:
            if not row:
                continue
            if head_info_count == 0:
                row_first = row
                head_info_count += 1
            elif head_info_count == 1:
                row_second = row
                head_info_count += 1
            elif head_info_count == 2:
                break
    
    if not row_first or not row_second:
        return (-1, "csv file missing header .", '')
    # print(row_first)
    # print(row_second)
    ret_row_first = []
    for i in range(len(row_first)):
        # print(row_first[i],  row_second[i])
        if "Note" in row_first[i] or "NOTE" in row_first[i] or "note" in row_first[i]:
            continue
        ret_row_first.append( {"index": i, "colkey":row_first[i] });
        field_key = row_first[i]
        field_typename = row_second[i].split('_')[1]
        
        csv_head_dict[field_key] = {'typename': field_typename}
    return (0, csv_head_dict, ret_row_first)
    

def row_list_data_to_dict(title, row):
    kvl = {}
    for i in range(len(title)):
        kvl[ title[i]['colkey'] ] = row[ title[i]['index'] ]
    return kvl


def csv_to_list(msg_desc, csv_path, enum_json):
    conv_enum_result = []

    # parse head from csv
    rv, csv_head_dict, csv_title_list = get_csv_head(csv_path)
    if rv != 0:
        return (-1, "parse csv : {f} filed, strerror: {msg}".format(f=csv_path, msg=csv_head_dict))
    # print(csv_title_list)
    # print("================================================CSV HEADER================================================")
    # print(csv_head_dict)
    # print("================================================CSV HEADER================================================")

    # parse body
    with open(csv_path, 'r', encoding='gbk') as csv_file:
        csv_reader = csv.reader(csv_file)
        skip_cnt = 0
        for row in csv_reader:
            if not row:
                continue
            if skip_cnt < 2:
                skip_cnt += 1
                continue
            row_dict = row_list_data_to_dict(csv_title_list, row)
            conv_enum_name(msg_desc, row_dict, enum_json, csv_head_dict)
            conv_enum_result.append(row_dict)
    return (0, conv_enum_result)


def fill_message_row(msg_desc, msg_row_inst, excel_row, col_name_prefix=''):
    for field_desc  in msg_desc.fields:
        field_name = field_desc.name
        field_cpptype = field_desc.cpp_type
        field_type = field_desc.type

        if field_is_repeated(field_desc):
            rename = camel_style_name(field_name)
            num_key= rename+'.num'
            if field_is_message(field_desc):
                field_obj = getattr(msg_row_inst, field_name)
                field_repeat_len = 0 if not excel_row[num_key] else int(excel_row[num_key])
                for idx in range(field_repeat_len):
                    fill_message_row(field_desc.message_type, field_obj.add(), excel_row, "{field}__{i}.".format(field=rename,i=idx))
            else:
                field_repeat = getattr(msg_row_inst, field_name)
                field_repeat_len = 0 if not excel_row[num_key] else int(excel_row[num_key])
                for idx in range(field_repeat_len):
                    field_repeat.extend([ excel_row[rename+"__"+idx] ])
        else:
            if field_is_message(field_desc):
                field_obj = getattr(msg_row_inst, field_name)
                fill_message_row(field_desc.message_type, field_obj, excel_row, rename+".")
            else:
                rename = col_name_prefix + camel_style_name(field_name)
                try:
                    setattr(msg_row_inst, field_name, excel_row[rename])
                except Exception as e:
                    raise Exception("set attr failed, attr:%s" % rename)
    # end fill_message_row

def conv_to_msg(msg_desc, msg_inst, list_data):
    for excel_row in list_data:
        msg_row = msg_inst.list.add()
        fill_message_row(msg_desc, msg_row, excel_row)

def __csv2pbin(csv_path, pbin_path, senv):
    if not os.path.exists(csv_path):
        return (-1, "csv_path don't exists .", False)

    # # conv to utf-8
    # csv_path_utf8 = csv_path.replace('.csv', '_utf8.csv')
    # with open(csv_path, "rb") as fdsrc , open(csv_path_utf8, 'wb') as fddest:
    #     fddest.write(fdsrc.read(1024*1024*10).decode('gbk').encode('utf-8'))
    # # xxx.csv -> xxx_gbk.csv
    # csv_path_gbk = csv_path.replace('.csv', '_gbk.csv')
    # os.system("mv {} {}".format(csv_path, csv_path_gbk))
    # # xxx_utf8.csv -> xxx.csv
    # os.system("mv {} {}".format(csv_path_utf8, csv_path))

    pbin_dirname = os.path.dirname(pbin_path)
    if not os.path.exists(pbin_dirname):
        os.mkdirs(pbin_dirname)

    gen_path = os.path.join(os.getcwd(), "game_proto", senv, "gen")
    sys.path.append(gen_path)
    res_u3_pb2 = __import__('res_u3_pb2')
    btl_u3_pb2 = __import__('btl_u3_pb2')
    sys.path.remove(gen_path)

    is_btl_bt = False
    msg_desc = get_message_descriptor(btl_u3_pb2, get_message_name(csv_path))
    if msg_desc:
        is_btl_bt = True

    # enum json
    enum_json = None
    enum_json_path = gen_path + '/res_u3.enum.json'
    if is_btl_bt:
        enum_json_path = gen_path + '/btl_u3.enum.json'
    with open(enum_json_path, 'r') as enj:
        enum_json = json.load(enj)
    if not enum_json:
        return (-2, "load {} .enum.json failed ."%(enum_json_path), False)

    #make message from csv
    if is_btl_bt == True:
        msg_desc = get_message_descriptor(btl_u3_pb2, get_message_name(csv_path))
        msg_type = get_message_type(btl_u3_pb2, "TB"+get_message_name(csv_path))
        if not msg_desc or not msg_type:
            return (-3, "get_message_descriptor or get_message_type failed .", False)
    else:
        msg_desc = get_message_descriptor(res_u3_pb2, get_message_name(csv_path))
        msg_type = get_message_type(res_u3_pb2, "TB"+get_message_name(csv_path))
        if not msg_desc or not msg_type:
            return (-4, "get_message_descriptor or get_message_type failed .", False)
    msg_inst = msg_type()

    res, list_data = csv_to_list(msg_desc, csv_path, enum_json)
    # print(list_data)
    
    conv_to_msg(msg_desc, msg_inst, list_data)
    pbmessage = msg_inst

    print("conv csv :{} to pbin :{} finish ...".format(csv_path, pbin_path))

    # write pbin
    if os.path.exists(pbin_path):
        os.chmod(pbin_path, stat.S_IRWXG+stat.S_IRWXU)
    
    with open(pbin_path, "wb") as fd:
        fd.write(pbmessage.SerializeToString())
    
    # wriete txt
    excel_txt_path = pbin_path.replace('.data', '.txt')
    if os.path.exists(excel_txt_path):
        os.chmod(excel_txt_path, stat.S_IRWXG + stat.S_IRWXU)
    
    with open(excel_txt_path, "w") as fd:
        print(text_format.MessageToString(pbmessage, as_utf8=True), file=fd)

    # check parse
    # msg_inst_for_parse = msg_type()
    # with open(pbin_path, 'rb') as fd:
    #     alldata = fd.read(1024*1024*10)
    #     msg_inst_for_parse.ParseFromString(alldata)
    #     print(text_format.MessageToString(msg_inst_for_parse, as_utf8=True, as_one_line=True))
    
    return (0, "{} conv to {} finish .".format(csv_path, pbin_path), is_btl_bt)


# return (retcode, msg)
def csv_to_pbin(csv_path, pbin_path, senv):
    try:
        return __csv2pbin(csv_path, pbin_path, senv)
    except Exception as e:
        exc_type, exc_value, exc_traceback = sys.exc_info()
        print("*** format_exception:")
        print(traceback.format_exc())
        msg = repr(traceback.format_exception(exc_type, exc_value, exc_traceback))
        raise Exception(msg)
    return (0, "OK .")






#######################################################
# test

# if __name__ == '__main__':
    # print(is_number('战役配表'))
    # print(is_number('123'))
    # print(is_number('123.5'))
    # print(is_number('.5'))
    # print(is_number(''))

    # csv_to_pbin("a", "b")
    # print(get_message_name("/home/alen/convtbu3/target_tables/u3_main/192.168.1.83/LevelDesc_Hot_角色等级经验表.csv"))
    # csv_file = "/home/alen/convtbu3/target_tables/u3_main/192.168.1.83/BattleLevelDesc_Hot_战役配表_test.csv"
    # pbin_file = "/home/alen/convtbu3/target_tables/u3_main/192.168.1.83/TBBattleLevelDesc.pbin"
    # print(get_message_name("./target_tables/u3_main/192.168.1.83/LevelDesc_Hot_角色等级经验表.csv"))
    # csv_to_pbin(csv_file, pbin_file)
