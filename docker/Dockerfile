FROM ubuntu:20.04

ADD WebcamDownloaderLinux_20.04_cli /bin/
RUN apt-get update && \
    apt-get -y install openssl && \
    chmod +x /bin/WebcamDownloaderLinux_20.04_cli && \
    mkdir -p /app/config
ENV WEBCAM_DOWNLOADER_OPTIONS_DIR=/app/config
ENTRYPOINT ["/bin/WebcamDownloaderLinux_20.04_cli"]
