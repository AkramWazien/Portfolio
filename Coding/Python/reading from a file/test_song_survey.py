from survey import AnonymousSurvey as AS

def test_store_single_response():
    question = 'What is your favourite song?'
    survey = AS(question)
    survey.store_response('Casablanca')
    assert 'Casablanca' in survey.responses

def test_store_three_response():
    question = 'What is your favourite song?'
    survey = AS(question)
    responses = ['Casablanca', 'Circus', 'In the blink of an eye']
    for response in responses:
        survey.store_response(response)

    for response in responses:
        assert  response in survey.responses