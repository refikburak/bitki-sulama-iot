# Otomatik Bitki Sulama Sistemi

Bu proje, NodeMCU ESP-8266 mikrodenetleyici, pervane, DC motor, toprak nem algılama sensörü, su pompası ve L9119 Çift Motor Sürücü Kartı kullanılarak geliştirilmiştir. Projenin amacı, bitkilerin sulama işlemini otomatikleştirmek ve toprak nem seviyesini kontrol etmektir.

## Özellikler
* Arduino platformu kullanılarak kodlama yapılmıştır.
* Mobil cihaz üzerinden kontrol edilen bir uygulama geliştirilmiştir.
* Blynk platformu kullanılarak uygulama arayüzü oluşturulmuştur.
* Uygulamadaki butonlar sayesinde fan ve pompa manuel olarak açılıp kapatılabilir.
* Toprak nem seviyesi, toprak nem algılama sensörü aracılığıyla okunur.
* Güncel nem oranı ThingSpeak platformu üzerinden tweet olarak paylaşılabilir.
* Otomatik mod, kullanıcının belirlediği nem oranına göre fanı ve pompayı otomatik olarak kontrol eder.
## Gereksinimler
* NodeMCU ESP-8266 mikrodenetleyici
* Pervane
* DC motor
* Toprak nem algılama sensörü
* Su pompası
* L9119 Çift Motor Sürücü Kartı
* Arduino IDE
* Blynk kütüphanesi
## Uygulama Arayüzü
![Ana Ekran](https://github.com/refikburak/bitki-sulama-iot/assets/82650577/2547e4b2-a3e2-4bdc-836e-e137fde870fe)

Nem oranının görüntülendiği, manuel olarak fan ve pompa kontrolünün sağlandığı ve tweet atılabilen sayfa.

![Otomatik Kontrol Ekranı](https://github.com/refikburak/bitki-sulama-iot/assets/82650577/5dd83ba4-137d-4af2-96c7-cf60ce93251f)

Fan ve pompanın otomatik çalışması için istenen nem oranlarının belirlendiği ve otomatik çalışma kontrolünün sağlandığı sayfa.
