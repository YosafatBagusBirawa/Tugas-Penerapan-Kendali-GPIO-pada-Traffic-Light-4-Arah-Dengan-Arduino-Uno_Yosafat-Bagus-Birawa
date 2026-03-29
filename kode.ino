/*
  traffic light control 4 arah

  program ini digunakan untuk mensimulasikan sistem lampu lalu lintas 4 arah
  menggunakan 12 buah led yang merepresentasikan lampu merah, kuning, dan hijau.

  prinsip kerja sistem:
  - arduino mengontrol masing-masing led menggunakan fungsi digitalwrite().
  - waktu nyala setiap lampu diatur menggunakan fungsi delay().
  - sistem bekerja secara otomatis dan berulang (looping).
  - lampu hijau menyala bergiliran searah jarum jam (utara -> timur -> selatan -> barat).
  - menggunakan fungsi modular aktifkansimpang() untuk mencegah konflik.

  catatan:
  - resistor digunakan untuk membatasi arus agar led tidak rusak.
  - kondisi default: semua lampu dalam kondisi merah sebelum satu sisi aktif.
  - durasi: hijau 5s, kuning kedip 3x lalu nyala 2s, merah menyala kembali.

*/

// sisi utara
const int u_rledPin = 13;
const int u_yledPin = 12;
const int u_gledPin = 11;

// sisi timur
const int t_rledPin = 10;
const int t_yledPin = 9;
const int t_gledPin = 8;

// sisi selatan
const int s_rledPin = 7;
const int s_yledPin = 6;
const int s_gledPin = 5;

// sisi barat
const int b_rledPin = 4;
const int b_yledPin = 3;
const int b_gledPin = 2;

void setup() {
  // semua led sebagai output
  pinMode(u_rledPin, OUTPUT); pinMode(u_yledPin, OUTPUT); pinMode(u_gledPin, OUTPUT);
  pinMode(t_rledPin, OUTPUT); pinMode(t_yledPin, OUTPUT); pinMode(t_gledPin, OUTPUT);
  pinMode(s_rledPin, OUTPUT); pinMode(s_yledPin, OUTPUT); pinMode(s_gledPin, OUTPUT);
  pinMode(b_rledPin, OUTPUT); pinMode(b_yledPin, OUTPUT); pinMode(b_gledPin, OUTPUT);

  // kondisi default: semua lampu dalam kondisi merah sebelum satu sisi aktif
  resetSemuaMerah();
}

void loop() {
  // lampu hijau menyala bergiliran searah jarum jam: utara -> timur -> selatan -> barat -> ulangi
  aktifkanSimpang(u_rledPin, u_yledPin, u_gledPin);
  aktifkanSimpang(t_rledPin, t_yledPin, t_gledPin);
  aktifkanSimpang(s_rledPin, s_yledPin, s_gledPin);
  aktifkanSimpang(b_rledPin, b_yledPin, b_gledPin);
}


// fungsi untuk memastikan kondisi awal aman (semua merah)
void resetSemuaMerah() {
  digitalWrite(u_rledPin, HIGH); digitalWrite(u_yledPin, LOW); digitalWrite(u_gledPin, LOW);
  digitalWrite(t_rledPin, HIGH); digitalWrite(t_yledPin, LOW); digitalWrite(t_gledPin, LOW);
  digitalWrite(s_rledPin, HIGH); digitalWrite(s_yledPin, LOW); digitalWrite(s_gledPin, LOW);
  digitalWrite(b_rledPin, HIGH); digitalWrite(b_yledPin, LOW); digitalWrite(b_gledPin, LOW);
}

// fungsi untuk modularisasi 
void aktifkanSimpang(int rPin, int yPin, int gPin) {
  // matikan lampu merah di simpang yang sedang aktif
  digitalWrite(rPin, LOW);

  // lampu hijau: menyala selama 5 detik
  digitalWrite(gPin, HIGH);
  delay(5000);
  digitalWrite(gPin, LOW);

  // lampu kuning: diberikan efek kedip 3 kali 
  for (int i = 0; i < 3; i++) {
    digitalWrite(yPin, HIGH);
    delay(250); 
    digitalWrite(yPin, LOW);
    delay(250); 
  }
  // dan menyala stabil selama 2 detik
  digitalWrite(yPin, HIGH);
  delay(2000); 
  digitalWrite(yPin, LOW);

  // lampu merah: menyala kembali setelah hijau dan kuning selesai
  digitalWrite(rPin, HIGH);
}
