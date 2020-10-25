# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.145.0/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version: bionic, focal
ARG VARIANT="focal"
FROM ubuntu:groovy

# [Optional] Uncomment this section to install additional OS packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends --reinstall ca-certificates \
    && apt-get -y install --no-install-recommends git build-essential gdb cmake ninja-build curl unzip tar

# # Use latest gcc version
# RUN apt-get -y install --no-install-recommends software-properties-common &&
#     add-apt-repository -y ppa:ubuntu-toolchain-r/test &&
#     apt-get -y install --no-install-recommends g++-11


