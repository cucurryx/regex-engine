import os
import sys

def get_filenames():
    filenames = os.listdir('./graphs')
    return [x for x in filenames if x[-3:] == 'dot']

def main():
    filenames = get_filenames()
    for each in filenames:
        os.system('dot graphs/' + each + ' -T png -o graphs/' + each[0:-4] + '.png')
    os.system('rm -rf graphs/*.dot')

main()
