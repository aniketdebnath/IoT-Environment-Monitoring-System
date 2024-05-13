import serial
import pymysql

dbConn=pymysql.connect(
    host="localhost",
    user="aniket22",
    password="",
    database="sensor_data_db"
)

device='/dev/ttyS0'

arduino=serial.Serial(device,9600)

cursor=dbConn.cursor()

def control_actuators(temperature,light_level):
    if temperature>30:
        print("High Temperature alert!")
    if light_level<100:
        print("Low light alert!")

while True:
    data=arduino.readline()
    data=data.decode('utf-8').strip()
    print(data)
    
    parts=data.split(',')
    try:
        if len(parts)>=3:
            hum=float(parts[0])
            temp=float(parts[1])
            light=int(parts[2])
        
        query="""
        INSERT INTO readings(temperature,humidity,light_level)
        VALUES(%s,%s,%s)
        """
        
        values=(temp,hum,light)
        
        cursor.execute(query,values)
        dbConn.commit()
        
        control_actuators(temp,light)
        
    except Exception as e:
        print("Failed to insert data:",e)
dbConn.close()