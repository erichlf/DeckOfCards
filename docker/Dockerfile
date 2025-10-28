FROM ubuntu:latest as base

ENV DEV_USER=dev

RUN apt-get update && \
  apt-get install -y --no-install-recommends \
    build-essential \
    clang-format \
    cmake \
    curl \
    git \
    g++ \
    libgtest-dev \
    openssh-client \
    unzip \
    tar \
  && apt-get autoremove -y \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/googletest
RUN cmake . && \
  cmake --build . && \
  cp ./lib/libgtest*.a /usr/lib

# user 1000 already exists as ubuntu on the system so fix that
RUN usermod -l $DEV_USER ubuntu \
  # [Optional] Add sudo support for the non-root user
  && apt-get update \
  && apt-get install -y --no-install-recommends sudo \
  && echo $DEV_USER ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$DEV_USER \
  && chmod 0440 /etc/sudoers.d/$DEV_USER

USER $DEV_USER

# Set up the entrypoint
CMD ["bash"]
