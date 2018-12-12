import os.path
import xmltodict
import json

def loadJSON():
    with open('/home/pi/projects/OpenDrone_FC/CONFIG.xml') as fd:
        doc = xmltodict.parse(fd.read())

    if 'accesspointName' in doc['opendrone'] or 'accesspointPassword' in doc['opendrone']:
        if os.path.isfile('/etc/accesspoint/accesspoint.json') is False:
            os.system('sudo touch /etc/accesspoint/accesspoint.json')

        json_data=open('/etc/accesspoint/accesspoint.json').read()

        j = json.loads(json_data)
        name=''
        pwd=''
        if 'accesspointName' in doc['opendrone']:
            name = doc['opendrone']['accesspointName']
            if name is None:
                name = j['ssid']
            

        if 'accesspointPassword' in doc['opendrone']:
            pwd = doc['opendrone']['accesspointPassword']
            if pwd is None:
                pwd = j['password']

        with open('/etc/accesspoint/accesspoint.json', 'w+') as f:
                f.write('{"ssid": "'+str(name)+'", "inet": null, "wlan": "wlan0", "password": "'+str(pwd)+'", "netmask": "255.255.255.0", "ip": "192.168.1.254"}')
                f.seek(0)

os.system('sudo pyaccesspoint stop')
if os.path.isfile('/etc/accesspoint/accesspoint.json'):
    loadJSON()
    os.system("sudo pyaccesspoint --config start")
else:
    cmd="sudo bash "+os.path.dirname(os.path.realpath(__file__))+"/install.sh"
    os.system(cmd)
    loadJSON()
    os.system("sudo pyaccesspoint --config start")