from pathlib import Path
import datetime
import matplotlib.pyplot as plt
import csv

path = Path('weather file/sitka_weather_2021_full.csv')
lines = path.read_text().splitlines()
reader = csv.reader(lines)
header_row = next(reader)

dates, precipitates = [], []
for row in reader:
    precipitate = float(row[5])
    date = datetime.datetime.strptime(row[2], '%Y-%m-%d')
    precipitates.append(precipitate)
    dates.append(date)

plt.style.use('seaborn-v0_8')
fig, ax = plt.subplots()
ax.plot(dates, precipitates, color='blue')
ax.set_xlabel('Time', fontsize=16)
ax.set_ylabel('Precipitations (cm cubed)', fontsize=16)
ax.set_title('Precipitations for year 2021 in sitka', fontsize=24)
ax.tick_params(labelsize=10)
fig.show()