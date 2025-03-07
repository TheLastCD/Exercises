
import os
from dotenv import load_dotenv
import spotipy
from spotipy.oauth2 import SpotifyOAuth
import pprint

# Load environment variables from .env file
load_dotenv()


# Get environment variables
client_id = os.getenv('SPOTIPY_CLIENT_ID')
client_secret = os.getenv('SPOTIPY_CLIENT_SECRET')
redirect_uri = os.getenv('SPOTIPY_REDIRECT_URI')

# Set up authentication
scope = "user-library-read"
sp = spotipy.Spotify(auth_manager=SpotifyOAuth(
    client_id=client_id,
    client_secret=client_secret,
    redirect_uri=redirect_uri,
    scope=scope
))

# Get user's liked songs
results = sp.current_user_saved_tracks()
tracks = results['items']
while results['next']:
    results = sp.next(results)
    tracks.extend(results['items'])

# Print the liked songs
for idx, item in enumerate(tracks):
    print(type(item))
    track = item['track']['album']
    pprint.pprint(track)
    break
