from flask import Flask, render_template, request, redirect, url_for,jsonify
import pymysql
import serial

app = Flask(__name__)

# Database configuration
db = pymysql.connect(
    host="localhost",
    user="aniket22", 
    password="", 
    database="sensor_data_db"
)

# Serial port configuration
ser = serial.Serial('/dev/ttyS0', 9600)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        if 'new_threshold' in request.form:
            new_threshold = request.form['new_threshold']
            command = f"SET_TEMP:{new_threshold}\n"
            ser.write(command.encode())
            print(f"Sent to Arduino: {command.strip()}")  # Log the command being sent
        if 'new_light_level' in request.form:
            new_light_level = request.form['new_light_level']
            command = f"SET_LIGHT:{new_light_level}\n"
            ser.write(command.encode())
            print(f"Sent to Arduino: {command.strip()}")  # Log the command being sent
        
        return redirect(url_for('index'))
        
    cursor = db.cursor(pymysql.cursors.DictCursor)
    cursor.execute("SELECT * FROM readings ORDER BY id DESC LIMIT 1")
    data = cursor.fetchone()
    cursor.close()
    return render_template('index.html', data=data)

@app.route('/analysis')
def analysis():
    cursor = db.cursor(pymysql.cursors.DictCursor)
    cursor.execute("""
        SELECT AVG(temperature) as avg_temp, MIN(temperature) as min_temp, MAX(temperature) as max_temp,
               AVG(light_level) as avg_light, MIN(light_level) as min_light, MAX(light_level) as max_light
        FROM readings
    """)
    result = cursor.fetchone()
    cursor.close()
    return render_template('analysis.html', analysis=result)

@app.route('/fetch-data')
def fetch_data():
    local_db = pymysql.connect(host="localhost", user="aniket22", password="", database="sensor_data_db")
    cursor = local_db.cursor(pymysql.cursors.DictCursor)
    cursor.execute("SELECT * FROM readings ORDER BY id DESC LIMIT 1")
    data = cursor.fetchone()
    cursor.close()
    print(data)
    local_db.close()  # Close connection after the query
    return jsonify(data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080, debug=True)
