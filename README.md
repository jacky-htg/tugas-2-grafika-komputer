# Script Presentasi Video
## [Intro] - Efraim's Voice

"Hi semuanya, perkenalkan kami dari kelompok 1 IT-601 Grafika Komputer PJJ Informatika Universitas Siber Asia. Kelompok Kami terdiri dari Rijal Asepnugroho, Efraim Semapua, Septia Azhar Nugraha dan Ahmad Hemdi. Pada video kali ini, kita akan membuat aplikasi paint sederhana menggunakan C++ dengan library GTK dan Cairo. Yuk, kita mulai!"

## [Segment 1: Mengenalkan GTK dan Cairo]

"Sebelum kita mulai, mari kita bahas sedikit tentang GTK dan Cairo. GTK adalah toolkit untuk membuat antarmuka grafis atau GUI. Ini sangat populer dan digunakan di banyak aplikasi Linux, tetapi juga dapat digunakan di platform lain seperti Windows dan macOS. Cairo adalah library grafis 2D yang mendukung berbagai backends output, termasuk X Window System, Win32, dan macOS. Cairo menyediakan antarmuka yang konsisten untuk menggambar pada berbagai perangkat."

## [Segment 2: Membuat Window Area Gambar]

"Baik, sekarang kita lihat kodenya. Pertama-tama, kita membuat sebuah kelas bernama MyArea yang mewarisi dari Gtk::DrawingArea. Di sini, kita menyiapkan event handler untuk menangani event mouse, seperti klik dan gerakan. Kita juga mendefinisikan warna default untuk menggambar, yaitu hitam."

```
class MyArea : public Gtk::DrawingArea {
public:
    MyArea() {
        // Setup event handlers for drawing
        add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK);
        current_color.set_rgba(0.0, 0.0, 0.0); // Default color is black
    }
    // ...
};
```
"Untuk segmen selanjutnya, saya persilahkan saudara Azhar untuk membawakannya."

## [Segment 3: Menggambar Sesuai Pergerakan Mouse] - Azhar's Voice

"Terima kasih, mari kita lihat bagaimana kita menggambar di area ini. Kita menggunakan vector untuk menyimpan garis yang digambar. Setiap kali mouse diklik, kita mulai sebuah garis baru, dan saat mouse digerakkan dengan tombol ditekan, kita tambahkan titik-titik baru ke garis tersebut."

```
bool on_button_press_event(GdkEventButton* event) override {
    if (event->button == 1) {
        current_line.clear();
        current_line.push_back({Gdk::Point(event->x, event->y), current_color});
        lines.push_back(current_line);
    }
    return true;
}

bool on_motion_notify_event(GdkEventMotion* event) override {
    if (event->state & GDK_BUTTON1_MASK) {
        lines.back().push_back({Gdk::Point(event->x, event->y), current_color});
        queue_draw(); // Request a redraw of the widget
    }
    return true;
}
```

"Dengan begini, kita akan membuat gambar berdasarkan pergerakan mouse ketika mouse dalam keadaan diklik. Untuk fitur selanjutnya, saya persilahkan sauadara Hemdi untuk membawakannya."

## [Segment 4: Fitur Clear] - Hemdi's voice

"Selanjutnya, kita tambahkan fitur untuk membersihkan gambar. Ini bisa dilakukan dengan menghapus semua garis yang ada dan meminta ulang gambar."

```
void clear() {
    lines.clear();
    queue_draw(); // Request a redraw of the widget
}
```

"Hopla! kita berhasil menambahkan fitur clear dalam aplikasi paint. Untuk fitur selanjutanya, saya persilahkan saudara Rijal untuk membawakannya."

## [Segment 5: Fitur Select Color] - Rijal's voice

"OK. Kita juga tambahkan fitur untuk memilih warna. Kita menggunakan Gtk::ColorButton untuk ini. Ketika warna dipilih, kita perbarui warna saat ini."

```
void set_color(const Gdk::RGBA& color) {
    current_color = color;
}
```

## [Segment 6: Demo Aplikasi]

"Sekarang, mari kita lihat bagaimana aplikasi ini bekerja. Kita akan menambahkan semua komponen ke window, termasuk area gambar, tombol clear, dan tombol warna. Kemudian kita jalankan aplikasinya."

```
int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "com.rijalasepnugroho");

    Gtk::Window window;
    window.set_default_size(800, 600);

    Gtk::Box vbox(Gtk::ORIENTATION_VERTICAL);
    window.add(vbox);

    MyArea area;
    vbox.pack_start(area);

    Gtk::Button button("Clear");
    button.signal_clicked().connect([&]() {
        area.clear();
    });
    vbox.pack_start(button, Gtk::PACK_SHRINK);

    Gtk::ColorButton color_button;
    color_button.signal_color_set().connect([&]() {
        Gdk::RGBA color = color_button.get_rgba();
        area.set_color(color);
    });
    vbox.pack_start(color_button, Gtk::PACK_SHRINK);

    window.show_all_children();

    return app->run(window);
}
```

"Dan inilah hasilnya. Kita bisa menggambar di area, memilih warna yang berbeda, dan membersihkan gambar dengan menekan tombol clear."

## [Outro]

"Itulah cara membuat aplikasi paint sederhana menggunakan C++ dengan GTK dan Cairo. Terima kasih sudah menonton. Sampai jumpa di video berikutnya!"
