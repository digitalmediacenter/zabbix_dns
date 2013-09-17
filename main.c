/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <err.h>
#include <getopt.h>
#include <sys/time.h>

/* ldns */
#include <stdbool.h>
#include <ldns/ldns.h>

static const char *g_progname;
static const char *g_progname_short;

static void help(void);
static void usage(void);
static void version(void);
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1);

static struct option longopts[] = {
    {"help", no_argument, NULL, 'h'},
    {"port", required_argument, NULL, 'p'},
    {"recurse", no_argument, NULL, 'r'},
    {"speed", no_argument, NULL, 's'},
    {"type", required_argument, NULL, 't'},
    {"version", no_argument, NULL, 1},
    {NULL, 0, NULL, 0}
};


/* Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1){
       long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
        result->tv_sec = diff / 1000000;
        result->tv_usec = diff % 1000000;
        return (diff<0);
}


int main(int argc, char **argv) {
    const char *domain = NULL;
    const char *server = NULL;
    ldns_resolver *resolver = NULL;
    ldns_rdf *rdf = NULL;
    ldns_pkt *pkt = NULL;
    ldns_rr_list *rrlist = NULL;
    ldns_status status;
    ldns_rr_type type = LDNS_RR_TYPE_SOA;
    struct timeval tv;
    char *ptr;
    int ch;
    unsigned short port = 53;
    signed char recurse = false;
    signed char speed = false;
    uint16_t flags = 0;
    struct timeval tvBegin, tvEnd, tvDiff;

    /* make argv[0] globally available */
    g_progname = argv[0];
    ptr = argv[0];
    while(*ptr) {
        ++ptr;
    }
    while(ptr > argv[0] && *(ptr - 1) != '/') {
        --ptr;
    }
    g_progname_short = ptr;

    /* parse command line options */
    while((ch = getopt_long(argc, argv, "shp:rt:", longopts, NULL)) != -1) {
        switch (ch) {
            case 0:
                break;
            case 1:            /* version */
                version();
                exit(EXIT_SUCCESS);
            case 'h':
                help();
                exit(EXIT_SUCCESS);
            case 'p':
                port = strtoul(optarg, NULL, 10);
                if(port == 0) {
                    warnx("Parameter port is malformed (1-65535).");
                    usage();
                }
                break;
            case 'r':
                recurse = true;
                flags |= LDNS_RD;
                break;
            case 's':
                speed = true;
                break;
            case 't':
                if(!strncasecmp("soa", optarg, 3)) {
                    type = LDNS_RR_TYPE_SOA;
                }
                else if(!strncasecmp("a", optarg, 1)) {
                    type = LDNS_RR_TYPE_A;
                }
                else {
                    warnx("Parameter type is malformed (must be 'soa' or 'a').");
                    usage();
                }
                break;
            default:
                usage();
        }
    }
    argc -= optind;
    argv += optind;

    /* command line arguments */
    if(argc != 2) {
        usage();
    }
    server = argv[0];
    domain = argv[1];

    /* get fresh resolver */

    gettimeofday(&tvBegin, NULL);

    resolver = ldns_resolver_new();
    if(!resolver) {
        if (speed){
            puts("0.0");
        }else{
            puts("0");
        }
        err(EXIT_FAILURE, NULL);
        exit(EXIT_FAILURE);
    }

    /* set options */
    ldns_resolver_set_recursive(resolver, recurse);
    ldns_resolver_set_dnssec(resolver, false);
    ldns_resolver_set_fail(resolver, true);
    ldns_resolver_set_dnsrch(resolver, false);
    ldns_resolver_set_defnames(resolver, false);
    ldns_resolver_set_random(resolver, false);
    ldns_resolver_set_port(resolver, port);
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    ldns_resolver_set_timeout(resolver, tv);


    /* set nameserver */
    rdf = ldns_rdf_new_frm_str(LDNS_RDF_TYPE_A, server);
    if(!rdf) {
        ldns_resolver_deep_free(resolver);
        if (speed){
            puts("0.0");
        }else{
            puts("0");
        }
        errx(EXIT_FAILURE, "malformed request to server %s",server);
        exit(EXIT_FAILURE);
    }


    status = ldns_resolver_push_nameserver(resolver, rdf);
    if(status != LDNS_STATUS_OK) {
        ldns_rdf_deep_free(rdf);
        ldns_resolver_deep_free(resolver);
        if (speed){
            puts("0.0");
        }else{
            puts("0");
        }
        err(EXIT_FAILURE, "%s", ldns_get_errorstr_by_id(status));
        exit(EXIT_FAILURE);
    }
    ldns_rdf_deep_free(rdf);

    /* parse domain name */
    rdf = ldns_dname_new_frm_str(domain);
    if(!rdf) {
        ldns_resolver_deep_free(resolver);
        if (speed){
            puts("0.0");
        }else{
            puts("0");
        }
        err(EXIT_FAILURE, "line %u", __LINE__);
        exit(EXIT_FAILURE);
    }
    ldns_dname2canonical(rdf);

    /* send query */
    pkt = ldns_resolver_query(resolver, rdf, type, LDNS_RR_CLASS_IN, flags);
    ldns_rdf_deep_free(rdf);

    if(!pkt) {
        ldns_resolver_deep_free(resolver);
        if (speed){
            puts("0.0");
        }else{
            puts("0");
        }
        errx(EXIT_FAILURE, "No response from %s", server);
        exit(EXIT_FAILURE);
    }
    /* get the SOA records from the answer section */
    rrlist = ldns_pkt_rr_list_by_type(pkt, type, LDNS_SECTION_ANSWER);

    if(!rrlist) {
        if (speed){
            gettimeofday(&tvEnd, NULL);
            timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
            printf("%ld.%06ld", tvDiff.tv_sec, tvDiff.tv_usec);
        }else{
            puts("1");
        }
    }
    else {
        ldns_rr_list_deep_free(rrlist);
        if (speed){
               puts("0.0");
        }else{
               puts("0");
        }
    }

    /* cleanup */
    ldns_pkt_free(pkt);
    ldns_resolver_deep_free(resolver);
    exit(EXIT_SUCCESS);
}

void help(void) {
    version();
    puts("Copyright (c) 2012, Andreas Heil <ah@linux-hq.de>");
    puts("Copyright (c) 2013, Marc Schoechlin <ms@256bit.org>");
    printf("Usage: %s [OPTIONS] <SERVER> <DOMAIN>\n", g_progname);
    puts("Options:");
    puts("  -h, --help       Display this help and exit.");
    puts("  -p, --port=#     Port number to use (default: 53).");
    puts("  -r, --recurse    Enable recursion (default: off).");
    puts("  -s, --speed      Measure speed (default: off).");
    puts("  -t, --type=VALUE Request Type (default: soa).");
    puts("                   Possible values: a, soa");
    puts("      --version    Display version information and exit.");
    puts("Arguments:");
    puts("  SERVER           IPv4 address of the server (x.x.x.x).");
    puts("  DOMAIN           request DOMAIN (e.g.: linux-hq.de).");
}

void usage(void) {
    fprintf(stderr, "Usage: %s [OPTIONS] <SERVER> <DOMAIN>\n", g_progname);
    fprintf(stderr, "Try `%s --help' for more information.\n", g_progname);
    exit(EXIT_FAILURE);
}

void version(void) {
    printf("%s v%s (%s)\n", g_progname_short, VERSION, BUILDDATE);
}
