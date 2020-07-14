#!/bin/bash

dir=$(cd $(dirname $0); pwd)

cd ${dir}/client/cs_share

branch_name=$1
[ "$branch_name" = "" ] && branch_name=develop
git pull origin $branch_name
