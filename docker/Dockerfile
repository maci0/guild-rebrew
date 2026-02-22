FROM docker.io/library/debian:stable-slim

RUN dpkg --add-architecture i386 && \
    apt-get update -y && \
    apt-get install -y --no-install-recommends \
        wine wine64 wine32 python3 python3-pip python3-venv \
        git ca-certificates && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

ENV WINEDEBUG=-all

RUN wine wineboot 2>/dev/null; true

WORKDIR /gamatcher

COPY tools/MSVC600 /gamatcher/tools/MSVC600

RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"
RUN pip install --no-cache-dir pefile capstone

COPY docker/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
