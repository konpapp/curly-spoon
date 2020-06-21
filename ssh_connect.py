import paramiko as pmk

username = raw_input("Username: ")
password = raw_input("Password: ")

hostnames = ["hostname1","hostname2","hostname3"]

commands = ["hostname","nproc","ps aux","exit"]


client = pmk.SSHClient()

client.set_missing_host_key_policy(pmk.AutoAddPolicy())

for hostname in hostnames:
    try:
        client.connect(hostname=hostname, username=username, password=password)
    except:
        print("[!] Cannot connect to the SSH Server")
        exit()
    
    for command in commands:
        stdin, stdout, stderr = client.exec_command(command)
        if command == "hostname":
            firstPart = str("Hostname: "+str(stdout.read().decode()))
            continue
        elif command == "nproc":
            secondPart = str("Total CPUs: " + str(stdout.read().decode()))
            continue
        elif command == "ps aux":
            thirdPart = str("Running: " + str(stdout.read().decode()))
            continue
        print(firstPart+secondPart+thirdPart)
        err = stderr.read().decode()
        if err:
            print(err)

