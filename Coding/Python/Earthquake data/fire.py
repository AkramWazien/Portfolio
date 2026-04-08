import requests
import plotly.express as px

#Make an api call and check response
url = 'https://api.github.com/search/repositories'
url += '?q=language:python+sort:stars+stars:>10000'

headers = {'Accept': 'application/vnd.github.v3+json'}
r = requests.get(url, headers= headers)
print(f'Status code: {r.status_code}')

response_dict = r.json()

#process repository items
repo_dicts = response_dict['items']
print(f'Total repositories: {response_dict['total_count']}')
print(f'Complete results: {not response_dict['incomplete_results']}')

#process repository result
stars, repo_names = [], []
for repo_dict in repo_dicts:
    star = repo_dict['stargazers_count']
    repo_name = repo_dict['name']
    stars.append(star)
    repo_names.append(repo_name)

fig = px.bar(x = repo_names, y = stars)
fig.show()