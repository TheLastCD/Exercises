
import os
from dotenv import load_dotenv, dotenv_values
import spotipy
from spotipy.oauth2 import SpotifyOAuth

# Load environment variables from .env file
load_dotenv()

# Load the .env file as a dictionary
config = dotenv_values()

# Print the contents of the .env file
print("Contents of the .env file:")
for key, value in config.items():
    print(f"{key}={value}")
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
    track = item['track']
    print(f"{idx + 1}. {track['artists'][0]['name']} - {track['name']}")
