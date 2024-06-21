#include "smsh.h"

void freelist(char **list);
void *erealloc(void *p,size_t n);
char *newstr(char *s,int l);

char *makestring(char *buf){
    char *cp;

    buf[strlen(buf)-1] = '\0';
    cp = (char *)malloc(strlen(buf)+1);
    if (cp == NULL){
        fprintf(stderr,"no memory\n");
        exit(1);
    }
    strncpy(cp,buf,sizeof(cp));
    return cp;
}


char *next_cmd(const char *prompt,FILE *fp){
    char *buf;
    int bufspace = 0;
    int pos = 0;
    int c;

    std::cout<<prompt;
    while ((c = getc(fp)) != EOF) {
        if(pos + 1 >= bufspace){
            if(bufspace == 0)
                buf = reinterpret_cast<char*>(emalloc(BUFSIZ));
            else
                buf = reinterpret_cast<char*>(erealloc(buf,bufspace + BUFSIZ));
            bufspace += BUFSIZ;
        }
        if(c == '\n')
            break;
        buf[pos++] = c;
    }
    if(c == EOF && pos == 0)
        return NULL;
    buf[pos] = '\0';
    return buf;
}

#define is_delim(x) ((x) == ' '||(x) == '\t')

char **splitline(char *line){
    char **args;
    int spots = 0;
    int bufspace = 0;
    int argnum = 0;
    char *cp = line;
    char *start;
    int len;

    if(line == NULL)
        return NULL;

    args = reinterpret_cast<char**>(emalloc(BUFSIZ));
    bufspace = BUFSIZ;
    spots = BUFSIZ/sizeof(char *);

    while(*cp != '\0'){
        while (is_delim(*cp)) {
            cp++;
        }
        if(*cp == '\0')
            break;

        if(argnum +1 >= spots){
            args =reinterpret_cast<char**>(erealloc(args,bufspace+BUFSIZ));
            bufspace += BUFSIZ;
            spots += BUFSIZ/sizeof(char *);
        }

        start = cp;
        len = 1;
        while(*++cp != '\0' && !(is_delim(*cp)) ){
            len++;
        }
        args[argnum++] = newstr(start,len);
    }
    args[argnum] = NULL;
    return args;
}

char *newstr(char *s,int l){
    char *rv = reinterpret_cast<char*>(emalloc(l+1));

    rv[l] = '\0';
    strncpy(rv,s,l);
    return rv;
}

void freelist(char **list){
    char **cp = list;
    while(*cp)
        free(*cp++);
    free(list);
}

void *emalloc(size_t n){
    void *rv;
    if((rv = malloc(n)) == NULL)
        fatal("out of memory","",1);
    return rv;
}

void *erealloc(void *p,size_t n){
    void *rv;
    if((rv = realloc(p,n)) == NULL)
        fatal("realloc() failed","",1);
    return rv;
}












