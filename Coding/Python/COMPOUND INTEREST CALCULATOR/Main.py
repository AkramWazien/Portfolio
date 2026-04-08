principle = 0
rate = 0
time = 0
number = 0

while principle <= 0:
    principle = float(input('Please enter your principle amount (RM):'))
    if principle <= 0:
        print (f'Sorry,{principle} can not be less than or equal to 0')

while rate <= 0:
    rate = float(input('Please enter your rate amount (%):'))
    if rate <= 0:
        print (f'Sorry,{rate} can not be less than or equal to 0')

while time <= 0:
    time = float(input('Please enter your time amount (year):'))
    if time <= 0:
        print (f'Sorry,{time} can not be less than or equal to 0')

while number <= 0:
    number = float(input('Please enter your principle amount (RM):'))
    if number <= 0:
        print (f'Sorry,{number} can not be less than or equal to 0')

result = principle * pow(1 + ((rate/100)/number), (number * time))
print(f"{result:,.2f}")
