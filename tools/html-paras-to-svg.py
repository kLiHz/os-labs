from bs4 import BeautifulSoup

html_doc = ""

with open('html.in') as in_file:
    html_doc = in_file.read()

html_doc = '<div class="terminal">' + html_doc + '</div>'

soup = BeautifulSoup(html_doc, 'html.parser')
div = soup.find('div', {'class': 'terminal'})

elements = []

i = 0
maxlen = 0

for p in div.findChildren('p', recursive=False):
    # For each '<p>' tag in '<div>'
    # Each '<p>' makes up a 'line', thus becomes a '<text>' element

    line = '\t<text x="{}" y="{}">'.format(25, 50 + i * 25)

    for child in p.contents:
        if child.name == 'span':
            # make '<tspan>' from '<span>'

            contents = str(child.contents[0])

            style_attr = child.get('style').replace('color', 'fill')

            if contents.find('  ') != -1:
                style_attr += ' white-space: pre;'

            tspan = '<tspan style="{}">{}</tspan>'.format(style_attr, contents)

            line += tspan

        else:
            line += str(child.string)
    
    maxlen = max(maxlen, len(BeautifulSoup(line, 'lxml').get_text()))
    
    line += '</text>\n'
    i += 1
    elements.append(line)


width = max(720, maxlen * 12.5)
height = 50 + i * 25 + 20

bg_rect = '\t<rect x="0" y="0" width="{}" height="{}" fill="#222A35"/>\n'.format(width, height)
elements.insert(0, bg_rect)

svg = '<svg width="{}" height="{}" xmlns="http://www.w3.org/2000/svg">\n{}</svg>\n'

stylesheet = \
'\t<style>' \
'text { ' \
    'font-family: Consolas,"Courier New",monospace; ' \
    'font-weight: 400; ' \
    'font-size: 20px; ' \
    'fill: #CCCCCC; ' \
'}</style>\n' \

svg = svg.format(width, height, stylesheet + "".join(elements))

with open('out.svg', 'w') as out_file:
    out_file.write(svg)
