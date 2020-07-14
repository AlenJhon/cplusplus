#!/bin/bash

bash update_share.sh

cur_dir=$(cd $(dirname $0); pwd)
cd ${cur_dir}/game_proto

ROLE=`whoami`
VIRTUALENV_ENTRY_FLAG=convtbu3
CS_SHARE_PROTO=${cur_dir}/client/cs_share/proto/u3/
PYTHON=/home/${ROLE}/.${VIRTUALENV_ENTRY_FLAG}/venv/bin/python
PROTO=${cur_dir}/install/protobuf-3.11.4/bin/protoc

# hot update
cp ${CS_SHARE_PROTO}/base_u3.py ./ -f
cp ${CS_SHARE_PROTO}/res_u3.py ./ -f
# not hot
cp ${cur_dir}/client/cs_share/proto/share/btl_share.py ./ -f
cp ${CS_SHARE_PROTO}/btl_u3.py ./ -f

if [[ ! -d ${cur_dir}/game_proto/gen ]];then
    mkdir -p ${cur_dir}/game_proto/gen
fi

#gen enum.json
${PYTHON} base_u3.py --outdir=gen --import_path=./
${PYTHON} res_u3.py --outdir=gen --import_path=./
${PYTHON} btl_share.py --outdir=gen --import_path=./
${PYTHON} btl_u3.py --outdir=gen --import_path=./

#gen proto py
${PROTO} gen/base_u3.proto --python_out=./gen/ --proto_path=./gen/
${PROTO} gen/res_u3.proto --python_out=./gen/ --proto_path=./gen/
${PROTO} gen/btl_share.proto --python_out=./gen/ --proto_path=./gen/
${PROTO} gen/btl_u3.proto --python_out=./gen/ --proto_path=./gen/





# ==================================================================================
# jenkins
# ln -fs ${WORKSPACE}/client/cs_share ${WORKSPACE}/server/source/cs_share;

# cd ${WORKSPACE}/server/tools; bash initenv.sh;
# cd ${WORKSPACE}/server/source/; sh autobuild.sh rebuild install_dir=${install_dir}
# cd ${WORKSPACE}/server/build; make clean; make -j6 rescheck


# if [[ ! -d ${install_dir} ]];then
#     mkdir -p ${install_dir}
# fi
# cp ${WORKSPACE}/server/build/bin/rescheck ${install_dir}
# ${install_dir}/rescheck -G


# CS_SHARE_PROTO=${WORKSPACE}/client/cs_share/proto
# CS_SHARE_PROTO_U3=${CS_SHARE_PROTO}/u3
# CS_SHARE_PROTO_SHARE=${CS_SHARE_PROTO}/share
# CONVTBU3_HOME=/data/gsgame/convtbu3
# CONVTBU3_GAME_PROTO=${CONVTBU3_HOME}/game_proto
# CONVTBU3_GAME_PROTO_GEN=${CONVTBU3_GAME_PROTO}/gen

# VIRTUALENV_ENTRY_FLAG=convtbu3
# PYTHON=/home/gsgame/.${VIRTUALENV_ENTRY_FLAG}/venv/bin/python
# PROTO=${CONVTBU3_HOME}/install/protobuf-3.11.4/bin/protoc

# if [[ ! -d ${CONVTBU3_GAME_PROTO_GEN} ]];then
#     mkdir -p ${CONVTBU3_GAME_PROTO_GEN}
# fi

# # hot update
# cp ${CS_SHARE_PROTO_U3}/base_u3.py ${CONVTBU3_GAME_PROTO} -f
# cp ${CS_SHARE_PROTO_U3}/res_u3.py ${CONVTBU3_GAME_PROTO} -f
# # not hot
# cp ${CS_SHARE_PROTO_SHARE}/btl_share.py ${CONVTBU3_GAME_PROTO} -f
# cp ${CS_SHARE_PROTO_U3}/btl_u3.py ${CONVTBU3_GAME_PROTO} -f


# #gen enum.json
# ${PYTHON} ${CONVTBU3_GAME_PROTO}/base_u3.py --outdir=${CONVTBU3_GAME_PROTO_GEN} --import_path=${CONVTBU3_GAME_PROTO}
# ${PYTHON} ${CONVTBU3_GAME_PROTO}/res_u3.py --outdir=${CONVTBU3_GAME_PROTO_GEN} --import_path=${CONVTBU3_GAME_PROTO}
# ${PYTHON} ${CONVTBU3_GAME_PROTO}/btl_share.py --outdir=${CONVTBU3_GAME_PROTO_GEN} --import_path=${CONVTBU3_GAME_PROTO}
# ${PYTHON} ${CONVTBU3_GAME_PROTO}/btl_u3.py --outdir=${CONVTBU3_GAME_PROTO_GEN} --import_path=${CONVTBU3_GAME_PROTO}

# #gen proto py
# ${PROTO} ${CONVTBU3_GAME_PROTO_GEN}/base_u3.proto --python_out=${CONVTBU3_GAME_PROTO_GEN} --proto_path=${CONVTBU3_GAME_PROTO_GEN}
# ${PROTO} ${CONVTBU3_GAME_PROTO_GEN}/res_u3.proto --python_out=${CONVTBU3_GAME_PROTO_GEN} --proto_path=${CONVTBU3_GAME_PROTO_GEN}
# ${PROTO} ${CONVTBU3_GAME_PROTO_GEN}/btl_share.proto --python_out=${CONVTBU3_GAME_PROTO_GEN} --proto_path=${CONVTBU3_GAME_PROTO_GEN}
# ${PROTO} ${CONVTBU3_GAME_PROTO_GEN}/btl_u3.proto --python_out=${CONVTBU3_GAME_PROTO_GEN} --proto_path=${CONVTBU3_GAME_PROTO_GEN}


# /bin/sed -i "s#<path>.*<#<path>LOG_PATH<#g" ${install_dir}/rescheck.default.xml
# /bin/sed -i "s#<dir>.*<#<dir>RES_PATH<#g" ${install_dir}/rescheck.default.xml