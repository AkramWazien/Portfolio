from pathlib import Path
import json
import plotly.express as px

path = Path('json data/eq_data_30_day_m1.geojson')
contents = path.read_text(encoding='utf-8')
data = json.loads(contents)

all_eq_data = data['features']

mags, lons, lats, eq_titles = [], [], [], []
for eq_dict in all_eq_data:
    mags.append(eq_dict['properties']['mag'])
    lons.append(eq_dict['geometry']['coordinates'][0])
    lats.append(eq_dict['geometry']['coordinates'][1])
    eq_titles.append(eq_dict['properties']['title'])

title = 'Global Earthquakes'
fig = px.scatter_geo(lat=lats, lon=lons, title=title,
        color=mags,
        color_continuous_scale='Viridis',
        labels={'color':'Magnitude'},
        projection='natural earth',
        hover_name=eq_titles,
    )
fig.show()
