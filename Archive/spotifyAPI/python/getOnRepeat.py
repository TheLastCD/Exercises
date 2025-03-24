
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
# scope = "user-read-currently-playing"
scope = "user-read-private"
sp = spotipy.Spotify(auth_manager=SpotifyOAuth(
    client_id=client_id,
    client_secret=client_secret,
    redirect_uri=redirect_uri,
    scope=scope
))
sp.player

"spotify:playlist:37i9dQZF1Epx4MoM39EsoT"
# Get user's liked songs
results = sp.currently_playing()
pprint.pprint(results)
tracks = results['items']
while results['next']:
    results = sp.next(results)
    tracks.extend(results['items'])


# Print the liked songs
for idx, item in enumerate(tracks):
    track = item
    pprint.pprint(track)
