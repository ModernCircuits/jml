import pyautogui as gui


print(gui.size())
print(gui.position())
gui.moveTo(500, 350, duration=0.5)
gui.click()
gui.write('# Hello world!', interval=0.1)
# Hello world!
