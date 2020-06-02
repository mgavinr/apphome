# FAQ # Using a gateway #

# -----------------------------
# Configure host
# -----------------------------
route del default
route add default gw 192.168.99.24

# -----------------------------
# Configure ubuntu gateway
# -----------------------------
/etc/sysctl.conf
net.ipv4.conf.all.forwarding=1

# -
iptables -t nat -A POSTROUTING -s 192.168.99.0/24 -d 172.16.0.0/24 -j SNAT --to-source 172.16.16.94
# -

# -
#Where, 192.168.99.0/24 internal network, and 172.16.16.94 the address through which you need to go to the Internet, similarly prescribed other internal networks.
#
#    Addresses    Hosts    Netmask    Amount of a Class C
#/24 256          254      255.255.255.0    1
#/16 65536        65534    255.255.0.0    256
# -
