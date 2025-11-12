{
    int sock = socket(rawsock);
    char buf[2048]; 
    ssize_t len;
    while((len = recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL))> 0)
    {
       for(ssize_t i = 0; i +4 < len; ++i)
       {
           if(buf[i] == 'u' && buf[i + 1] == 's' && buf[i+2]=='e' && buf[i+3]=='r'
           {
               printf("credential-liek data : %ld bytes \n", len);
               break;
           }
       }
    }
    close(sock);
    return 0;
}
