# zabbix_dns

## About

"DNS Monitoring helper for [Zabbix][1]"

This tool sends a dns request to a defined server and report the time needed for the request or a zabbix status value regarding
the success of the dns request (also a empty answer is reported as successful).

This project is a fork of https://bitbucket.org/aheil/zabbix-dns

## Compile and Install

### Prerequisites:

 * C-Compiler
 * GNU Make
 * [ldns libraries][2]

On Ubuntu simply do:

        apt-get install build-essential ldnsutils libldns-dev

### Installation

        git clone git@github.com:digitalmediacenter/zabbix_dns.git
        cd zabbix_dns
        make
        make install

This will install the binary `zabbix_dns` to `/etc/zabbix/externalscripts`.

### Usage

        $ ./zabbix_dns --help
        zabbix_dns v1.2 (Tue Sep 17 16:21:13 CEST 2013)
        Copyright (c) 2012, Andreas Heil <ah@linux-hq.de>
        Copyright (c) 2013, Marc Schoechlin <ms@256bit.org>
        Usage: ./zabbix_dns [OPTIONS] <SERVER> <DOMAIN>
        Options:
          -h, --help       Display this help and exit.
          -p, --port=#     Port number to use (default: 53).
          -r, --recurse    Enable recursion (default: off).
          -s, --speed      Measure speed (default: off).
          -t, --type=VALUE Request Type (default: soa).
                           Possible values: a, soa
              --version    Display version information and exit.
        Arguments:
          SERVER           IPv4 address of the server (x.x.x.x).
          DOMAIN           request DOMAIN (e.g.: linux-hq.de).

### TODOs

 * check argv[1] for valid IPv4 address
 * implement IPv6
 * remove dependency to libldns
 * a error should be reportable if dns result is empty

## Authors

 * Andreas Heil <ah@linux-hq.de>
 * Marc Schoechlin <marc.schoechlin@dmc.de>

## License

[BSD 2-Clause License][3]:

> Copyright (c) 2012, Andreas Heil <ah@linux-hq.de>  
> All rights reserved.
> 
> Redistribution and use in source and binary forms, with or without
> modification, are permitted provided that the following conditions
> are met:
> 
>    1. Redistributions of source code must retain the above copyright
>    notice, this list of conditions and the following disclaimer.
>    2. Redistributions in binary form must reproduce the above copyright
>    notice, this list of conditions and the following disclaimer in the
>    documentation and/or other materials provided with the distribution.
> 
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
> AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
> IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
> ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
> LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
> CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
> SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
> INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
> CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
> ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
> POSSIBILITY OF SUCH DAMAGE.

[1]: http://www.zabbix.com
[2]: http://www.nlnetlabs.nl/projects/ldns/
[3]: http://opensource.org/licenses/BSD-2-Clause
[4]: https://bitbucket.org/aheil/zabbix-dns
