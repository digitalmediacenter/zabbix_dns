# zabbix_dns

## About

"DNS Monitoring helper for [Zabbix][1]"

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
