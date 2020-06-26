import os
import sys
import re
import csv
import xml.etree.ElementTree as et

def main(argv):

    if len(argv) < 2:
        return

    tree = et.parse(argv[0])
    root = tree.getroot()

    group = root.find('Group')

    csv_data = []

    for test_case in group:

        if test_case.tag != 'TestCase':
            continue

        if not test_case.attrib['name'].startswith('Benchmarks'):
            continue

        csv_data.append([test_case.attrib['name'], '', '', ''])
        csv_data.append(['nb items', 'low', 'mean', 'high'])

        for bm in test_case:

            if bm.tag != 'BenchmarkResults':
                continue

            m = re.search('(\w+\s+)+(\d+)', bm.attrib['name'])

            mean = bm.find('mean')

            a = mean.attrib

            csv_data.append([m.group(2), a['lowerBound'], a['value'], a['upperBound']])

    with open(argv[1], 'w') as f:
        writer = csv.writer(f)
        writer.writerows(csv_data)

if __name__ == '__main__':
   main(sys.argv[1:])