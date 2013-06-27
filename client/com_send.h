void ls_send(int ctlfd, struct sockaddr_in *server_addr,\
			CTL *ctl);
void push_send(int ctlfd, struct sockaddr_in *server_addr,\
			CTL *ctl);
void pull_send(int ctlfd, struct sockaddr_in *server_addr,\
			CTL *ctl);

