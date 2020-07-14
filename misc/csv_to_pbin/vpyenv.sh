#!/bin/bash
source_venv(){
    vname=$1
    vdp=$2
    VERSION=$3
    [ "$VERSION" == "" ] && VERSION=3.4
    [ "$vdp" == "" ] && vdp="."
    vp="${HOME}/.$1/venv"
    if [[ ! -d "$vp" ]];then
        echo "install virtual env with python=${VERSION} ..."
        virtualenv $vp --python=python${VERSION}
    fi
    source ${vp}/bin/activate
    pip install -r ${vdp}/requirements.txt | grep -v "equirement already satisfied"
}