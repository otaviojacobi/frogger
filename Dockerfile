FROM alpine:3.14

COPY . .

RUN apk add --update alpine-sdk
RUN apk add ncurses ncurses-dev
RUN make

CMD while : ; do echo "${MESSAGE=Idling...}"; sleep ${INTERVAL=600}; done