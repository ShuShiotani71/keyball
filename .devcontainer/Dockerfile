FROM ghcr.io/qmk/qmk_cli@sha256:2dc05fc9f32efebd6b05c2b8676ee548358bc7e151e9dbf4dac6b6eed4513b07

WORKDIR /root/

RUN apt update && apt install -y\
    vim\
    usbutils\
    openssh-client\
    tmux

# use dotfiles and devcoontainer built in support for this rather than writing in dockerfile
# COPY my_config/* /root/

RUN git clone https://github.com/qmk/qmk_firmware.git --depth 1 --recurse-submodules --shallow-submodules -b 0.22.14 qmk

WORKDIR /root/qmk

