from pathlib import Path
import csv
import matplotlib.pyplot as plt
from datetime import datetime

#path for death valley
path_death = Path('death_valley_2021_simple.csv')
#path for sitka
path_sitka = Path('sitka_weather_2021_simple.csv')

reader_death = list(csv.reader(Path.read_text(path_death).splitlines()))
reader_sitka = list(csv.reader(Path.read_text(path_sitka).splitlines()))
header_row_d = reader_death.pop(0)
header_row_s = reader_sitka.pop(0)


def get_weather_data(location, dates_index, high_index, low_index):
    dates, highs, lows = [], [], []
    for row in location:
        try:
            date = datetime.strptime(row[dates_index], '%Y-%m-%d')
            high = int(row[high_index])
            low = int(row[low_index])
        except ValueError:
            print(f'Data at {date} is unavailable')
        else:
            dates.append(date)
            highs.append(high)
            lows.append(low)
    return dates, highs, lows

dates, death_high, death_low = get_weather_data(reader_death,2,3,4)
_, sitka_high, sitka_low = get_weather_data(reader_sitka,2,4,5)

plt.style.use('seaborn-v0_8')
fig, ax = plt.subplots()
ax.plot(dates, death_high, color='red')
ax.plot(dates, death_low, color='blue')
ax.plot(dates, sitka_high, color='orange')
ax.plot(dates, sitka_low, color='green')
ax.fill_between(dates, death_high, death_low, color='red', alpha=0.5)
ax.fill_between(dates, sitka_high, sitka_low, color='orange', alpha=0.5)

ax.set_title('Graph of highs and lows temperature at sitka and death valley', fontsize=24)
ax.set_xlabel('', fontsize=16)
ax.set_xlabel('Temperature(F)', fontsize=16)
fig.autofmt_xdate()
fig.show()