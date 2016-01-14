import tweepy

consumer_key = "xuL0BDtuEpcfmndKKMAbNpZOX"
consumer_secret = "eXLHr23Roz8LJwLTtOZm01FTOSSknpKLzfepho4nujGa2L0An3"
access_token = "2405610432-anzHFrNNBx2AOVWic6jfO2X3YA2aT6jC82qxaI1"
access_token_secret = "MGT97vVvGyci0W1gOr5P44dTZy0PBD9zFu5K3UCvCU3ET"


auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_token_secret)

api = tweepy.API(auth)



