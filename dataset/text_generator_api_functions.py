import requests

url = "https://randommer.io/api/Text/LoremIpsum"

# pm me on telegram @ibragimovaidar if you need api key
API_KEY = "" # os.environ.get("RANDOMER_API_KEY")


def get_random_text(count_of_words: int) -> str:
    headers = {
        "X-Api-Key": API_KEY
    }
    params = {
        "loremType": "normal",
        "type": "words",
        "number": count_of_words
    }

    r = requests.get(url= url, headers=headers, params=params)

    return r.text


if __name__ == "__main__":
    print(get_random_text(50))