/*
 * Copyright (c) 2000 University of Utah and the Flux Group.
 * All rights reserved.
 * 
 * This file is part of the Flux OSKit.  The OSKit is free software, also known
 * as "open source;" you can redistribute it and/or modify it under the terms
 * of the GNU General Public License (GPL), version 2, as published by the Free
 * Software Foundation (FSF).  To explore alternate licensing terms, contact
 * the University of Utah at csl-dist@cs.utah.edu or +1-801-585-3271.
 * 
 * The OSKit is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GPL for more details.  You should have
 * received a copy of the GPL along with the OSKit; see the file COPYING.  If
 * not, write to the FSF, 59 Temple Place #330, Boston, MA 02111-1307, USA.
 */

#include <oskit/fudp.h>
#include <oskit/error.h>
#include <arpa/inet.h>

struct entry {
    char* ip;
    unsigned char eth[ETHER_ADDR_SIZE];
};

/* 
 * Note: I used to make every part of the IP address be 3 digits long
 * by preceding them with a 0.  But, this being Unix, this means they're
 * interpreted as octal numbers and... well, you can imagine the rest.
 */
/* Most of the following were obtained by running arp -a on thistle
 * or marker.  It helps to flood the network with pings first using
 * something like this:
 * sequence_ [ system $ "ping -n -c1 155.99.212." ++ show x ++ " &" | x <- [0..255] ]
 */

struct entry table[] =
{ 
#if 0 /* 212 direct */
  { "155.99.212.0",   {0xff, 0xff, 0xff, 0xff, 0xff, 0xff} },
  { "155.99.212.1",   {0x00, 0x60, 0xf5, 0x00, 0x04, 0x14} }, // fast
  { "155.99.212.13",  {0x00, 0xa0, 0xc9, 0x82, 0x82, 0xff} }, // cheap
  { "155.99.212.23",  {0x00, 0x60, 0x08, 0x8f, 0x70, 0x9b} }, // mancos
  { "155.99.212.58",  {0x00, 0x00, 0xc0, 0x56, 0x0c, 0x9f} }, // leak
  { "155.99.212.59",  {0x00, 0xa0, 0xc9, 0x61, 0x6c, 0x8e} }, // mug
  { "155.99.212.61",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x41} }, // marker
  { "155.99.212.62",  {0x00, 0xa0, 0xc9, 0x61, 0x66, 0xd7} }, // ink
  { "155.99.212.68",  {0x08, 0x00, 0x09, 0x86, 0x01, 0x03} }, // waver
  { "155.99.212.71",  {0x08, 0x00, 0x09, 0x24, 0xa4, 0xb4} }, // harpo
  { "155.99.212.74",  {0x00, 0x90, 0x27, 0xca, 0x70, 0x41} }, // plastic
  { "155.99.212.80",  {0x00, 0xa0, 0xc9, 0xf1, 0x10, 0xe2} }, // alta
  { "155.99.212.81",  {0x00, 0xa0, 0xc9, 0xf1, 0x80, 0xc0} }, // eden
  { "155.99.212.82",  {0x00, 0xa0, 0xc9, 0xdd, 0xaa, 0x1e} }, // eureka
  { "155.99.212.83",  {0x00, 0xa0, 0xc9, 0xf1, 0x7a, 0x06} }, // ibapah
  { "155.99.212.84",  {0x00, 0xa0, 0xc9, 0xf1, 0xbc, 0xfe} }, // ioka
  { "155.99.212.85",  {0x00, 0xa0, 0xc9, 0xf1, 0x82, 0x4b} }, // irontown
  { "155.99.212.86",  {0x00, 0xa0, 0xc9, 0xf1, 0x49, 0x7b} }, // kamas
  { "155.99.212.87",  {0x00, 0xa0, 0xc9, 0xf1, 0xbc, 0xff} }, // peerless
  { "155.99.212.88",  {0x00, 0xa0, 0xc9, 0xf1, 0x49, 0xde} }, // moab
  { "155.99.212.89",  {0x00, 0x00, 0xc0, 0x42, 0x65, 0xe4} }, // snowville
  { "155.99.212.90",  {0x00, 0xa0, 0xc9, 0xf1, 0x9c, 0x66} }, // thistle
  { "155.99.212.91",  {0x00, 0xa0, 0xc9, 0xf1, 0x7b, 0xc1} }, // torrey
  { "155.99.212.92",  {0x00, 0xa0, 0xc9, 0xf1, 0xbc, 0xe5} }, // washakie
  { "155.99.212.93",  {0x00, 0xa0, 0xc9, 0xf1, 0x5b, 0x7b} }, // zane
  { "155.99.212.94",  {0x00, 0xa0, 0xc9, 0xf1, 0xbd, 0x01} }, // nephi
  { "155.99.212.95",  {0x00, 0xa0, 0xc9, 0xf1, 0x7e, 0x99} }, // sego
  { "155.99.212.96",  {0x00, 0xa0, 0xc9, 0xf1, 0x80, 0xcc} }, // cornish
  { "155.99.212.112", {0x00, 0x60, 0x08, 0x8f, 0x7c, 0x94} }, // axl
  { "155.99.212.119", {0x00, 0xa0, 0xc9, 0xee, 0x1e, 0x3b} }, // eroica
  { "155.99.212.126", {0x00, 0x80, 0x1c, 0xc8, 0x88, 0x00} }, // gw-css
  { "155.99.212.134", {0x08, 0x00, 0x20, 0x1a, 0xd5, 0x13} }, // filesave
  { "155.99.212.137", {0x00, 0x60, 0x08, 0x8f, 0x7c, 0x94} }, // rawk
  { "155.99.212.138", {0x00, 0x60, 0x08, 0x8f, 0x7c, 0x94} }, // vandy
  { "155.99.212.153", {0x00, 0xa0, 0xc9, 0x66, 0x38, 0x4d} }, // paria
  { "155.99.212.193", {0x08, 0x00, 0x09, 0x94, 0xb8, 0xd1} }, // cssps0
  { "155.99.212.195", {0x00, 0x60, 0xb0, 0xba, 0x99, 0x48} },
  { "155.99.212.206", {0x00, 0xa0, 0xc9, 0xe1, 0x15, 0x61} }, // coke 
  { "155.99.212.207", {0x00, 0xa0, 0xc9, 0x6c, 0x86, 0xc6} }, // doughnut
  { "155.99.212.241", {0x00, 0xa0, 0x00, 0x40, 0xcb, 0xbc} },
  { "155.99.212.255", {0xff, 0xff, 0xff, 0xff, 0xff, 0xff} },
#endif /* 212 */
#if 1 /* 212 via marker - note that all use marker's ethernet address */
  { "155.99.212.1",   {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.13",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.23",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.61",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.80",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.81",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.83",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.84",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.85",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.86",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.87",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.88",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.89",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.90",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.91",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.92",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.93",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.94",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.95",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.96",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.112", {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.126", {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.153", {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.207", {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
  { "155.99.212.255", {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} },
#endif /* 212 */
#if 1 /* direct connections to the 214 subnet */
  { "155.99.214.0",   {0xff, 0xff, 0xff, 0xff, 0xff, 0xff} },
  { "155.99.214.61",  {0x00, 0x00, 0x92, 0xa7, 0x54, 0x42} }, // marker
  { "155.99.214.69",  {0x00, 0x00, 0xc0, 0x52, 0x0c, 0x9f} }, // bellies
  { "155.99.214.71",  {0x08, 0x00, 0x09, 0x66, 0x76, 0x6b} }, // peacock
  { "155.99.214.72",  {0x00, 0xc0, 0xb7, 0x92, 0x6d, 0x1a} }, // soybeans
  { "155.99.214.88",  {0x00, 0x60, 0xf5, 0x04, 0x00, 0x53} },
  { "155.99.214.142", {0x00, 0xa0, 0xc9, 0x86, 0x04, 0xf5} }, // mish

//  { "155.99.214.153", {0x00, 0x40, 0x11, 0x08, 0x40, 0x29} }, // magpie
//  { "155.99.214.153", {0x00, 0x40, 0x33, 0x2c, 0x65, 0x2b} }, // magpie1
  { "155.99.214.153", {0x00, 0x40, 0x33, 0x2b, 0xc8, 0xd3} }, // magpie2

  { "155.99.214.158", {0x00, 0x00, 0xc0, 0x06, 0xd2, 0xe4} }, // dicey
  { "155.99.214.159", {0x00, 0x00, 0xc0, 0x04, 0xd2, 0xe4} }, // iffy
  { "155.99.214.163", {0x00, 0x00, 0xc0, 0x55, 0x0c, 0x9f} }, // maybe
  { "155.99.214.164", {0x00, 0x00, 0xc0, 0x37, 0x0c, 0x9f} }, // quirky
  { "155.99.214.165", {0x00, 0x00, 0xc0, 0x03, 0xd2, 0xe4} }, // flaky
  { "155.99.214.170", {0x02, 0x90, 0x27, 0xad, 0xba, 0xd4} },
  { "155.99.214.171", {0x02, 0x90, 0x27, 0xad, 0x24, 0xc3} }, 
  { "155.99.214.201", {0x08, 0x00, 0x2b, 0x81, 0x65, 0xe8} }, // dnard1
  { "155.99.214.202", {0x08, 0x00, 0x2b, 0x81, 0x63, 0x70} }, // dnard2
  { "155.99.214.203", {0x08, 0x00, 0x2b, 0x81, 0x61, 0x1b} }, // dnard3
  { "155.99.214.204", {0x08, 0x00, 0x2b, 0x81, 0x64, 0x1f} }, // dnard4
  { "155.99.214.208", {0x08, 0x00, 0x2b, 0x81, 0x63, 0xb5} }, // dnard8
  { "155.99.214.222", {0x08, 0x00, 0x2b, 0x81, 0x5f, 0xa6} },
  { "155.99.214.223", {0x08, 0x00, 0x2b, 0x81, 0x66, 0x03} },
  { "155.99.214.224", {0x08, 0x00, 0x2b, 0x81, 0x60, 0x54} },
  { "155.99.214.225", {0x08, 0x00, 0x2b, 0x81, 0x65, 0xc7} },
  { "155.99.214.242", {0x00, 0x00, 0x81, 0x3b, 0x29, 0x94} },
  { "155.99.214.255", {0xff, 0xff, 0xff, 0xff, 0xff, 0xff} },

#endif /* 214 */
#if 0 // router subnet
  { "155.99.214.150", {0x00, 0xa0, 0xc9, 0x82, 0x89, 0x94} }, // falcon fxp0 0xffffff00
  { "155.99.213.185", {0x00, 0xa0, 0xc9, 0xdb, 0xcc, 0x62} }, // falcon fxp1 0xfffffff8 broadcast 155.99.213.191
//  { "???.??.???.???", {0x00, 0x90, 0x27, 0xa4, 0x9e, 0xa6} }, // falcon fxp2

  { "155.99.214.151", {0x00, 0xa0, 0xc9, 0x61, 0x66, 0xd1} }, // chukar fxp0 0xffffff00 broadcast 155.99.214.255
  { "155.99.213.190", {0x00, 0xa0, 0xc9, 0xdb, 0xf7, 0xb4} }, // chukar fxp1 0xfffffff8 broadcast 155.99.213.191
  { "155.99.213.198", {0x00, 0x90, 0x27, 0xa4, 0xa0, 0xbc} }, // chukar fxp2 0xfffffff8 broadcast 155.99.213.199

  { "155.99.214.156", {0x00, 0xa0, 0xc9, 0x61, 0x6c, 0xa4} }, // vulture fxp0 0xffffff00
  { "155.99.213.193", {0x00, 0x90, 0x27, 0xa4, 0xa0, 0xb8} }, // vulture fxp1 0xfffffff8 broadcast 155.99.213.199
//  { "???.??.???.???", {0x00, 0x90, 0x27, 0xa4, 0x9e, 0x96} }, // vulture fxp2
#else
  { "155.99.214.150", {0x00, 0xa0, 0xc9, 0x82, 0x89, 0x94} }, // falcon
  { "155.99.214.151", {0x00, 0xa0, 0xc9, 0x61, 0x66, 0xd1} }, // chukar
  { "155.99.214.156", {0x00, 0xa0, 0xc9, 0x61, 0x6c, 0xa4} }, // vulture
#endif
}; 

oskit_error_t
init(void) 
{
    int i;
    struct in_addr ipaddr;
    oskit_error_t err;

    for(i = 0; i < sizeof(table) / sizeof(struct entry); ++i) {
        int rc = inet_aton(table[i].ip, &ipaddr);
        if (!rc) return 1;  // inet_aton returns 1 for success

	err = farp_add(&ipaddr, table[i].eth);
        if (err) return err;
    }
    return 0;
}

