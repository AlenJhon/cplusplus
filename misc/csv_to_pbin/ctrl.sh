#!/bin/bash
VIRTUALENV_ENTRY_FLAG=convtbu3
ACTIVATE=/home/gsgame/.${VIRTUALENV_ENTRY_FLAG}/venv/bin/activate
PYTHON_BIN=python3
MAIN_PY=convtbu3.py
PYTHON_VERSION=3.7


start(){
    source ${ACTIVATE}
    nohup ${PYTHON_BIN} ${MAIN_PY} &
}

stop(){
    proc_num=`ps -ef | grep python  | grep ${VIRTUALENV_ENTRY_FLAG} | grep -v grep | wc -l`

    if [[ ${proc_num} -gt 0 ]]; then
        proc_id=`ps -ef | grep python  | grep ${VIRTUALENV_ENTRY_FLAG} | grep -v grep | awk '{print $2}'`
        kill -9 ${proc_id}
    fi
}

restart(){
    stop
    start
}

initenv(){
    cur_dir="$(cd $(dirname $0); pwd)"
    echo "current dir: ${cur_dir}"
    echo "install default tools ..."

    sudo apt-get install python${PYTHON_VERSION} python-virtualenv -y

    cd ${cur_dir}
    source ./vpyenv.sh
    source_venv ${VIRTUALENV_ENTRY_FLAG} . ${PYTHON_VERSION}
    pip install git+ssh://git@git.gs.com:36001/gsbase/pbdc.git@trunk --upgrade

    client_dir="${cur_dir}/client/"
    if [ ! -d "${client_dir}" ];then
        echo "check clone share ..."
        mkdir -p ${client_dir}
        cd ${client_dir}
        git init
        git remote add -f origin ssh://git@git.gs.com:36001/gs_client/ue4_client.git
        git config core.sparsecheckout true
        echo "cs_share/" >> .git/info/sparse-checkout
        git pull origin develop 
    fi

    if [ ! -d "${cur_dir}/install/protobuf-3.11.4" ];then
        echo "make install protobuf ..."
        cd ${cur_dir}/install
        bash make_install_protobuf-3.11.4.sh
    fi
}

check_restart(){
    cur_dir=$(cd $(dirname $0);pwd)

    proc_num=`ps -ef | grep python  | grep ${VIRTUALENV_ENTRY_FLAG} | grep -v grep | wc -l`

    if [[ ${proc_num} -eq 0 ]]; then
        echo 'no proc running, start...'
        cd ${cur_dir} 
        start
    # else
        # echo 'proc is running'
    fi
}


list(){
    echo "usage: bash $1 <option>"
    echo "option as follow:"
    echo -e "\tstart"
    echo -e "\tstop"
    echo -e "\trestart"
    echo -e "\tinitenv"
    echo -e "\tcheck_restart"
}


case $1 in
    start)
        start
        ;;
    stop)
        stop
        ;;
    restart)
        restart
        ;;
    initenv)
        initenv
        ;;
    check_restart)
        check_restart
        ;;
    *)
        list
esac
