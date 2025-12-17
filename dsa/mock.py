import requests
from bs4 import BeautifulSoup

def decodeSecretMessage(url):
    response = requests.get(url)
    if response.status_code != 200:
        print("Document invalid")
        return
    
    # Parsing the HTML table here..
    soup = BeautifulSoup(response.text, 'html.parser')
    table = soup.find('table')
    rows = table.find_all('tr')
    
    data = []
    maxX = 0
    maxY = 0
    
    for row in rows[1:]:
        cols = row.find_all('td')
        if len(cols) >= 3:
            # example format followed columns order - x-coordinate, character, y-coordinate
            try:
                x = int(cols[0].get_text().strip())
                char = cols[1].get_text().strip()
                y = int(cols[2].get_text().strip())
                
                data.append((x, y, char))
                
                # Track grid boundaries
                if x > maxX: maxX = x
                if y > maxY: maxY = y
            except ValueError:
                continue

    # Initialize the grid with spaces since grid size will be (maxX + 1) by (maxY + 1)
    grid = [[" " for _ in range(maxX + 1)] for _ in range(maxY + 1)]
    
    # now filling the grid but I am considering Y = 0 as top based on the sample "F" given
    for x, y, char in data:
        grid[y][x] = char

    # printing the grid (reversing y to ensure correct orientation)
    for r in range(maxY, -1, -1):
        print("".join(grid[r]))

decodeSecretMessage("https://docs.google.com/document/d/e/2PACX-1vSvM5gDlNvt7npYHhp_XfsJvuntUhq184By5xO_pA4b_gCWeXb6dM6ZxwN8rE6S4ghUsCj2VKR21oEP/pub")