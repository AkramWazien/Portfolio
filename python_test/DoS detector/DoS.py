import os
import sys
import time
from collections import defaultdict
from scapy.all import sniff, IP

THRESHOLD = 40
print(f'Threshold: {THRESHOLD}')
      
def packet_callback(packet):
    src_ip = packet[IP].src
    packet_count[src_ip] += 1

    current_time = time.time()
    interval_time = current_time - start_time[0]

    if interval_time >= 1:
        for count, ip in packet_count.items():
            packet_rate = count / interval_time
            #print(f'Ip: {ip} Packet rate: {packet_rate}')
            