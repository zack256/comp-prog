#!/bin/bash

set -e -u -o pipefail

top_dir_abs="$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)"
problem_group_dir="${top_dir_abs}/workspace/${1}"

single_problem_dir="${problem_group_dir}/${2}"
mkdir -p "${single_problem_dir}"
cd "${single_problem_dir}"
cp "${top_dir_abs}/base.cpp" .
touch \
    input.txt \
    output.txt \
    desired.txt