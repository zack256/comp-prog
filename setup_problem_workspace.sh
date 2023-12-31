TOP_WORKSPACE_RELATIVE_PATH="$(dirname "${BASH_SOURCE[0]}")/workspace"
TOP_WORKSPACE_ABSOLUTE_PATH=$(cd "${TOP_WORKSPACE_RELATIVE_PATH}" && pwd)
LOCAL_WORKSPACE_ABSOLUTE_PATH="${TOP_WORKSPACE_ABSOLUTE_PATH}/${1}"
mkdir -p "${LOCAL_WORKSPACE_ABSOLUTE_PATH}"
cp "${TOP_WORKSPACE_ABSOLUTE_PATH}/../base.cpp" "${LOCAL_WORKSPACE_ABSOLUTE_PATH}/sol.cpp"
touch "${LOCAL_WORKSPACE_ABSOLUTE_PATH}/input.txt"
touch "${LOCAL_WORKSPACE_ABSOLUTE_PATH}/output.txt"
touch "${LOCAL_WORKSPACE_ABSOLUTE_PATH}/desired.txt"