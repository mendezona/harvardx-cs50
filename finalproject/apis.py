import requests
from datetime import time, date, datetime

def lookupWeather():
    """Look up weather for court"""

    # Contact API
    try:
        response = requests.get(f"https://api.openweathermap.org/data/2.5/onecall?lat=-33.832879&lon=151.210593&units=metric&appid=38b25bbca2410e9103460ff0fdf5a9ed")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        weather = response.json()
        return {
            "test": weather["daily"],
            "futureRain": round(weather["hourly"][0]["pop"], 2),
            "sunset": datetime.fromtimestamp(weather["current"]["sunset"]),
            "feels_like": round(weather["current"]["feels_like"]),
            "wind_speed": weather["current"]["wind_speed"],
            "main": weather["current"]["weather"],
            "time": datetime.fromtimestamp(weather["current"]["dt"]),
            "current": weather["current"]["weather"][0]["description"]
        }

    except (KeyError, TypeError, ValueError):
        return None