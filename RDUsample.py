import requests

esp8266_ip = "192.168.216.65"

while True:
    mode = int(input("Enter mode (1-4, 0 to exit): "))
    
    if mode == 0:
        break

    url = f"http://{esp8266_ip}/{mode}"

    response = requests.get(url)
    print(response.text)

print("Exiting the script.")
