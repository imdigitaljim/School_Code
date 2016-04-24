from bs4 import BeautifulSoup
from datetime import datetime
import markovify, tweepy, time

def post_twitter(output):
    consumer_key = ""
    consumer_secret = ""
    access_token = "-"
    access_token_secret = ""
    auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
    auth.set_access_token(access_token, access_token_secret)
    api = tweepy.API(auth)
    print("posting" + str(datetime.now().time()))
    api.update_status(output)


corpus = open("corpus.txt", "r")
raw = corpus.read()
raw = BeautifulSoup(raw, "html.parser").get_text()
raw = raw.replace("\\r","").replace("\\n"," ").replace("\\","")
text_model = markovify.Text(raw)
while (True):
    post_twitter(text_model.make_short_sentence(140))
    time.sleep(3600)
