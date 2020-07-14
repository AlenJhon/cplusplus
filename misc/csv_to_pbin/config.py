#coding:utf-8
settings={}

settings['listen_port'] = 3000

# p4
settings['p4port']="p4.b1sz.gs.com:1666"
settings['p4user']="u3-server-builder"
settings['p4pass']="u3-server-builder"
settings['p4charset']="utf8"
settings['p4client']="gsgame_p4"
settings['p4_local_path_prefix']="/data/p4" 
settings['p4_remote_root_path']="//u3_main"
settings['p4_bin_path'] = '/home/gsgame/p4bin/p4'
settings['p4_sync_base_dir'] = '/data/p4_for_sync/u3/'

settings['p4_remote_pbtable_runtime'] = '//u3_main/{vbranch_tag}unreal_proj/Content/01_U3Main/PBTable/Runtime/'
settings['p4_remote_pbtable_none_runtime'] = '//u3_main/{vbranch_tag}unreal_proj/Content/01_U3Main/PBTable/NoneRuntime/'
# 
settings['is_show_cmd'] = True
settings['is_sync_p4'] = False


#
# settings['vbranch'] = {
#     'u3_main' : {
#         'vname':''
#     }
#     # 'u3_20201001_xx': {
#         # 'vname':'u3_20201001_xx'
#     # }
# }
