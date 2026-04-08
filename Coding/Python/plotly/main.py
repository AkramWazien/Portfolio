import pathlib
import csv
import matplotlib.pyplot as plt
import datetime

path = pathlib.Path('sitka_weather_2021_simple.csv')
lines = path.read_text().splitlines()

reader = (csv.reader(lines))
header_row = next(reader)

#Extract high temperatures
dates, highs, lows = [], [], []
for row in reader:
    date = datetime.datetime.strptime(row[2],'%Y-%m-%d')
    dates.append(date)
    high = int(row[4])
    highs.append(high)
    low = int(row[5])
    lows.append(low)

plt.style.use('seaborn-v0_8')
fig, ax = plt.subplots()
ax.plot(dates, highs, color='red', alpha=0.5)
ax.plot(dates, lows, color='blue', alpha=0.5)
ax.fill_between(dates, highs, lows, facecolor='green', alpha=0.1)
ax.set_xlabel('',fontsize=16)
ax.set_ylabel('Temperature (F)', fontsize=16)
ax.set_title('Daily high and lows temperatures')
fig.autofmt_xdate()
ax.tick_params(labelsize=16)
fig.show()
