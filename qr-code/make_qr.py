import qrcode
import qrcode.image.svg

factory = qrcode.image.svg.SvgPathImage
img = qrcode.make("https://sethrobles.github.io/qr", image_factory=factory, box_size=10, border=2)
with open("seth_qr_path.svg", "wb") as f:
    img.save(f)
print("Saved seth_qr_path.svg")
