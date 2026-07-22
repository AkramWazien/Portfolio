import random

ip_list = {
    '192.168.106.1': 'block',
    '192.168.106.68': 'allow',
    '192.168.106.49': 'block',
    '192.168.106.39': 'block',
    '192.168.106.180': 'allow',
    '192.168.106.148': 'block',
    '192.168.106.250': 'block',
    '192.168.106.34': 'allow',
    '192.168.106.74': 'allow',
    '192.168.106.18': 'block',
    '192.168.106.104': 'allow',
}

def random_ip():
    fourth_octet = random.randint(1,255)
    rand_ip = '192.168.106.'+str(fourth_octet)
    return str(rand_ip)

def check_ip_rules(ip_received):
    if ip_received in ip_list:
        return(ip_list[ip_received])
    else:
        return('ask for permission')

def main():
    for i in range (1, 60):
        ip = random_ip()
        action = check_ip_rules(ip)
        randnum = random.randint(1,9999)
        print(f'IP:{ip} Action:{action} Random:{randnum}')


if __name__ == '__main__':
    main()