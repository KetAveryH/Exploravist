import requests

headers = {
    "Authorization": "",
}

data = {
    "model": "text:audio",
    "input": "Your text here",
    "response_format": "wav",
}

response = requests.post("https://api.openai.com/v1/audio:speech",
                         headers=headers, json=data, stream=True)


if response.status_code == 200:
    for chunk in response.iter_content(chunk_size=1024):
        # Process each chunk (e.g., play it, save to a buffer, etc.)
else:
    print("Error:", response.status_code)
