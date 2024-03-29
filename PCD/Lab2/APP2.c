/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Laboratorul 2
 * 
 * < Scrieti scriptul C care afiseaza procesele 
 *  de pe sistem in ordinea descrescatoare 
 * a resurselor utilizate (CPU, memorie etc).
 * 
 * 
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * daca nu putem citii procesul
 */
#include <stdio.h> /* librarie pentru input output*/
#include <unistd.h> /* folosim fork si sleep*/
#include <stdlib.h> /* librarie standard pt exit() */
#include <sys/wait.h> /* wait() la sistem*/
#include <signal.h> /* folosim pt kill() */

int main(int argc,char* argv[])
{
    FILE *fp;
    char line[1025]; /* buffer pentru fiecare linie citita din comanda*/

   
    /* 'ps aux' comanda bash afișează procesele; 'sort -nrk 4' sortează rezultatele după coloana a patra (memoria), în ordine descrescătoare */
    char *command = "ps aux --sort=-%mem | awk '{print $11, $4, $3}'"; 

    /* citim */
    fp = popen(command, "r");
    /* tratam eroarea in care nu se ruleaza comanda */
    if (fp == NULL) 
    {
        printf("Failed to run command\n" );
        exit(EXIT_FAILURE);
    }

    /* afisam outputul linie cu linie */
    printf("Process\t\tMemory%%\tCPU%%\n"); /* Proces , memorie , cpu*/
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        printf("%s", line); 
    }

    /* Închidem procesul deschis de popen() */
    pclose(fp);
    return 0;
}
/* 
gcc -g -o app2 APP2.c 
./app2 

Process		Memory%	CPU%
COMMAND %MEM %CPU
/snap/firefox/3941/usr/lib/firefox/firefox 4.0 6.8
/snap/firefox/3941/usr/lib/firefox/firefox 2.8 0.9
/usr/bin/gnome-shell 2.6 8.1
/snap/firefox/3941/usr/lib/firefox/firefox 2.0 0.7
/usr/share/code/code 1.8 4.7
/snap/firefox/3941/usr/lib/firefox/firefox 1.6 1.5
/snap/firefox/3941/usr/lib/firefox/firefox 1.5 0.1
/snap/firefox/3941/usr/lib/firefox/firefox 1.4 0.2
/usr/share/code/code 1.2 2.2
/usr/share/code/code 1.2 0.6
/usr/lib/x86_64-linux-gnu/webkit2gtk-4.0/WebKitWebProcess 1.1 0.3
/snap/whatsapp-for-linux/58/usr/local/bin/whatsapp-for-linux 1.1 0.8
gnome-control-center 1.0 4.9
/usr/share/code/code 1.0 1.1
/snap/firefox/3941/usr/lib/firefox/firefox 0.9 0.3
/snap/firefox/3941/usr/lib/firefox/firefox 0.8 0.0
/usr/bin/Xwayland 0.8 0.7
/snap/firefox/3941/usr/lib/firefox/firefox 0.7 0.0
/usr/share/code/code 0.6 0.0
/snap/firefox/3941/usr/lib/firefox/firefox 0.6 0.0
/snap/firefox/3941/usr/lib/firefox/firefox 0.6 0.0
/usr/libexec/gsd-xsettings 0.6 0.0
/usr/share/code/code 0.5 0.3
/usr/share/code/code 0.5 0.0
/snap/firefox/3941/usr/lib/firefox/firefox 0.5 1.2
/snap/firefox/3941/usr/lib/firefox/firefox 0.5 0.0
/snap/firefox/3941/usr/lib/firefox/firefox 0.5 0.0
/snap/firefox/3941/usr/lib/firefox/firefox 0.5 0.0
gjs 0.4 0.0
/usr/share/code/code 0.4 0.0
/usr/lib/x86_64-linux-gnu/webkit2gtk-4.0/WebKitNetworkProcess 0.4 0.0
/usr/libexec/evolution-data-server/evolution-alarm-notify 0.4 0.0
/usr/share/code/code 0.4 0.0
/usr/libexec/gnome-terminal-server 0.4 0.2
/snap/firefox/3941/usr/lib/firefox/firefox 0.4 0.0
/usr/bin/gnome-calendar 0.4 0.0
/home/negrea/.vscode/extensions/ms-vscode.cpptools-1.19.8-linux-x64/bin/cpptools 0.3 0.9
/usr/libexec/xdg-desktop-portal-gnome 0.3 0.0
/snap/firefox/3941/usr/lib/firefox/firefox 0.3 0.0
/usr/share/code/code 0.3 0.0
/usr/share/code/code 0.3 0.0
/usr/libexec/goa-daemon 0.2 0.0
/usr/libexec/tracker-miner-fs-3 0.2 0.0
/usr/lib/snapd/snapd 0.2 0.0
update-notifier 0.2 0.0
/usr/bin/pulseaudio 0.2 0.0
/usr/libexec/evolution-calendar-factory 0.2 0.0
/usr/libexec/ibus-extension-gtk3 0.2 0.0
/usr/libexec/evolution-addressbook-factory 0.2 0.0
/usr/bin/gnome-terminal.real 0.1 0.0
/usr/bin/gnome-terminal.real 0.1 0.0
/usr/bin/gjs 0.1 0.0
/usr/bin/gjs 0.1 0.0
/usr/libexec/gsd-media-keys 0.1 0.0
/usr/bin/gnome-terminal.real 0.1 0.0
/lib/systemd/systemd-journald 0.1 0.0
/usr/libexec/gsd-color 0.1 0.0
/usr/libexec/evolution-source-registry 0.1 0.0
/usr/libexec/xdg-desktop-portal-gtk 0.1 0.0
/usr/libexec/gsd-power 0.1 0.0
/usr/libexec/ibus-x11 0.1 0.0
/usr/bin/python3 0.1 0.0
/usr/libexec/gsd-wacom 0.1 0.0
/snap/snapd-desktop-integration/83/usr/bin/snapd-desktop-integration 0.1 0.0
/usr/libexec/gsd-keyboard 0.1 0.0
/usr/libexec/gnome-shell-calendar-server 0.1 0.0
/usr/libexec/packagekitd 0.1 0.0
/usr/bin/python3 0.1 0.0
/usr/bin/snap 0.1 0.0
/usr/bin/python3 0.1 0.0
/usr/bin/python3 0.1 0.0
/usr/sbin/NetworkManager 0.1 0.0
/usr/bin/python3 0.1 0.0
/home/negrea/.vscode/extensions/ms-vscode.cpptools-1.19.8-linux-x64/bin/cpptools-srv 0.1 0.0
/usr/libexec/gnome-session-binary 0.1 0.0
/usr/libexec/gsd-datetime 0.1 0.0
/usr/libexec/gnome-session-binary 0.1 0.0
/usr/libexec/goa-identity-service 0.1 0.0
/usr/libexec/gsd-printer 0.1 0.0
/lib/systemd/systemd-resolved 0.1 0.0
/usr/libexec/xdg-desktop-portal 0.1 0.0
/snap/snapd-desktop-integration/83/usr/bin/snapd-desktop-integration 0.0 0.0
/home/negrea/.vscode/extensions/ms-vscode.cpptools-1.19.8-linux-x64/bin/cpptools-srv 0.0 0.0
/usr/sbin/cupsd 0.0 0.0
/usr/libexec/colord 0.0 0.0
/sbin/init 0.0 0.0
/usr/libexec/udisks2/udisksd 0.0 0.0
/usr/bin/ibus-daemon 0.0 0.0
/usr/sbin/ModemManager 0.0 0.0
/usr/share/code/code 0.0 0.0
/usr/sbin/cups-browsed 0.0 0.0
/usr/share/code/chrome_crashpad_handler 0.0 0.0
gdm-session-worker 0.0 0.0
/usr/libexec/gsd-print-notifications 0.0 0.0
/sbin/wpa_supplicant 0.0 0.0
/lib/systemd/systemd 0.0 0.0
/usr/libexec/gvfs-udisks2-volume-monitor 0.0 0.0
/usr/libexec/gsd-sharing 0.0 0.0
/usr/libexec/polkitd 0.0 0.0
/usr/libexec/gsd-sound 0.0 0.0
/usr/libexec/upowerd 0.0 0.0
/usr/libexec/gvfsd-trash 0.0 0.0
/usr/libexec/gvfsd-dnssd 0.0 0.0
/usr/sbin/gdm3 0.0 0.0
/usr/libexec/gvfsd-network 0.0 0.0
/usr/libexec/gvfsd 0.0 0.0
/usr/libexec/gvfs-afc-volume-monitor 0.0 0.0
/usr/libexec/gsd-smartcard 0.0 0.0
/lib/systemd/systemd-logind 0.0 0.0
/usr/libexec/at-spi-bus-launcher 0.0 0.0
/usr/libexec/accounts-daemon 0.0 0.0
/usr/libexec/gsd-housekeeping 0.0 0.0
/usr/libexec/gsd-disk-utility-notify 0.0 0.0
/usr/libexec/xdg-document-portal 0.0 0.0
/usr/libexec/ibus-portal 0.0 0.0
/usr/libexec/ibus-engine-simple 0.0 0.0
/usr/libexec/power-profiles-daemon 0.0 0.0
/usr/libexec/ibus-memconf 0.0 0.0
/usr/libexec/at-spi2-registryd 0.0 0.0
/lib/systemd/systemd-timesyncd 0.0 0.0
/usr/libexec/gvfs-gphoto2-volume-monitor 0.0 0.0
/usr/bin/gnome-keyring-daemon 0.0 0.0
/usr/libexec/gsd-a11y-settings 0.0 0.0
/lib/systemd/systemd-udevd 0.0 0.0
/usr/bin/pipewire 0.0 0.0
/lib/systemd/systemd-oomd 0.0 0.1
/usr/bin/pipewire-media-session 0.0 0.0
/usr/libexec/gvfs-mtp-volume-monitor 0.0 0.0
/usr/libexec/gsd-rfkill 0.0 0.0
/usr/libexec/switcheroo-control 0.0 0.0
/usr/libexec/gvfsd-fuse 0.0 0.0
/usr/libexec/gvfs-goa-volume-monitor 0.0 0.0
/usr/libexec/gvfsd-metadata 0.0 0.0
/usr/libexec/gsd-screensaver-proxy 0.0 0.0
/usr/libexec/xdg-permission-store 0.0 0.0
/usr/libexec/gdm-wayland-session 0.0 0.0
/usr/libexec/dconf-service 0.0 0.0
(sd-pam) 0.0 0.0
/usr/libexec/gnome-session-ctl 0.0 0.0
/usr/bin/dbus-daemon 0.0 0.0
/usr/bin/bash 0.0 0.0
bash 0.0 0.0
@dbus-daemon 0.0 0.0
bash 0.0 0.0
/usr/bin/bash 0.0 0.0
bash 0.0 0.0
bash 0.0 0.0
/usr/sbin/rsyslogd 0.0 0.0
/usr/lib/bluetooth/bluetoothd 0.0 0.0
/usr/bin/dbus-daemon 0.0 0.0
ps 0.0 0.0
/usr/sbin/irqbalance 0.0 0.0
avahi-daemon: 0.0 0.0
/usr/libexec/rtkit-daemon 0.0 0.0
/usr/sbin/cron 0.0 0.0
logger 0.0 0.0
awk 0.0 0.0
/usr/sbin/kerneloops 0.0 0.0
/usr/sbin/kerneloops 0.0 0.0
/usr/sbin/acpid 0.0 0.0
fusermount3 0.0 0.0
./app2 0.0 0.0
./app2 0.0 0.0
sh 0.0 0.0
sh 0.0 0.0
sh 0.0 0.0
./app2 0.0 0.0
avahi-daemon: 0.0 0.0
./app2 0.0 0.0
./app2 0.0 0.0
./app2 0.0 0.0
./app2 0.0 0.0
./app2 0.0 0.0
./app2 0.0 0.0
[kthreadd] 0.0 0.0
[rcu_gp] 0.0 0.0
[rcu_par_gp] 0.0 0.0
[slub_flushwq] 0.0 0.0
[netns] 0.0 0.0
[mm_percpu_wq] 0.0 0.0
[rcu_tasks_kthread] 0.0 0.0
[rcu_tasks_rude_kthread] 0.0 0.0
[rcu_tasks_trace_kthread] 0.0 0.0
[ksoftirqd/0] 0.0 0.0
[rcu_preempt] 0.0 0.0
[migration/0] 0.0 0.0
[idle_inject/0] 0.0 0.0
[cpuhp/0] 0.0 0.0
[cpuhp/2] 0.0 0.0
[idle_inject/2] 0.0 0.0
[migration/2] 0.0 0.0
[ksoftirqd/2] 0.0 0.0
[cpuhp/4] 0.0 0.0
[idle_inject/4] 0.0 0.0
[migration/4] 0.0 0.0
[ksoftirqd/4] 0.0 0.0
[cpuhp/6] 0.0 0.0
[idle_inject/6] 0.0 0.0
[migration/6] 0.0 0.0
[ksoftirqd/6] 0.0 0.0
[cpuhp/8] 0.0 0.0
[idle_inject/8] 0.0 0.0
[migration/8] 0.0 0.0
[ksoftirqd/8] 0.0 0.0
[cpuhp/10] 0.0 0.0
[idle_inject/10] 0.0 0.0
[migration/10] 0.0 0.0
[ksoftirqd/10] 0.0 0.0
[cpuhp/12] 0.0 0.0
[idle_inject/12] 0.0 0.0
[migration/12] 0.0 0.0
[ksoftirqd/12] 0.0 0.0
[cpuhp/14] 0.0 0.0
[idle_inject/14] 0.0 0.0
[migration/14] 0.0 0.0
[ksoftirqd/14] 0.0 0.0
[cpuhp/1] 0.0 0.0
[idle_inject/1] 0.0 0.0
[migration/1] 0.0 0.0
[ksoftirqd/1] 0.0 0.0
[cpuhp/3] 0.0 0.0
[idle_inject/3] 0.0 0.0
[migration/3] 0.0 0.0
[ksoftirqd/3] 0.0 0.0
[cpuhp/5] 0.0 0.0
[idle_inject/5] 0.0 0.0
[migration/5] 0.0 0.0
[ksoftirqd/5] 0.0 0.0
[cpuhp/7] 0.0 0.0
[idle_inject/7] 0.0 0.0
[migration/7] 0.0 0.0
[ksoftirqd/7] 0.0 0.0
[cpuhp/9] 0.0 0.0
[idle_inject/9] 0.0 0.0
[migration/9] 0.0 0.0
[ksoftirqd/9] 0.0 0.0
[cpuhp/11] 0.0 0.0
[idle_inject/11] 0.0 0.0
[migration/11] 0.0 0.0
[ksoftirqd/11] 0.0 0.0
[cpuhp/13] 0.0 0.0
[idle_inject/13] 0.0 0.0
[migration/13] 0.0 0.0
[ksoftirqd/13] 0.0 0.0
[cpuhp/15] 0.0 0.0
[idle_inject/15] 0.0 0.0
[migration/15] 0.0 0.0
[ksoftirqd/15] 0.0 0.0
[kdevtmpfs] 0.0 0.0
[inet_frag_wq] 0.0 0.0
[kauditd] 0.0 0.0
[khungtaskd] 0.0 0.0
[oom_reaper] 0.0 0.0
[writeback] 0.0 0.0
[kcompactd0] 0.0 0.0
[ksmd] 0.0 0.0
[khugepaged] 0.0 0.0
[kintegrityd] 0.0 0.0
[kblockd] 0.0 0.0
[blkcg_punt_bio] 0.0 0.0
[tpm_dev_wq] 0.0 0.0
[ata_sff] 0.0 0.0
[md] 0.0 0.0
[md_bitmap] 0.0 0.0
[edac-poller] 0.0 0.0
[devfreq_wq] 0.0 0.0
[watchdogd] 0.0 0.0
[irq/25-AMD-Vi] 0.0 0.0
[kswapd0] 0.0 0.0
[ecryptfs-kthread] 0.0 0.0
[kthrotld] 0.0 0.0
[irq/28-pciehp] 0.0 0.0
[kworker/7:1-events] 0.0 0.0
[acpi_thermal_pm] 0.0 0.0
[mld] 0.0 0.0
[ipv6_addrconf] 0.0 0.0
[kstrp] 0.0 0.0
[kworker/u33:0-hci0] 0.0 0.0
[charger_manager] 0.0 0.0
[irq/31-MSFT0001:00] 0.0 0.0
[nvme-wq] 0.0 0.0
[nvme-reset-wq] 0.0 0.0
[nvme-delete-wq] 0.0 0.0
[nvme-auth-wq] 0.0 0.0
[jbd2/nvme0n1p6-8] 0.0 0.0
[ext4-rsv-conver] 0.0 0.0
[cfg80211] 0.0 0.0
[cryptd] 0.0 0.0
[amd_iommu_v2] 0.0 0.0
[napi/phy0-8194] 0.0 0.0
[napi/phy0-8195] 0.0 0.0
[napi/phy0-8196] 0.0 0.0
[nvkm-disp] 0.0 0.0
[ttm] 0.0 0.0
[mt76-tx 0.0 0.0
[kworker/u33:2-hci0] 0.0 0.0
[amdgpu-reset-de] 0.0 0.0
[ttm] 0.0 0.0
[amdgpu_dm_hpd_r] 0.0 0.0
[amdgpu_dm_hpd_r] 0.0 0.0
[dm_vblank_contr] 0.0 0.0
[card1-crtc0] 0.0 0.0
[card1-crtc1] 0.0 0.0
[card1-crtc2] 0.0 0.0
[card1-crtc3] 0.0 0.0
[gfx_low] 0.0 0.2
[gfx_high] 0.0 0.1
[comp_1.0.0] 0.0 0.0
[comp_1.1.0] 0.0 0.0
[comp_1.2.0] 0.0 0.0
[comp_1.3.0] 0.0 0.0
[comp_1.0.1] 0.0 0.0
[comp_1.1.1] 0.0 0.0
[comp_1.2.1] 0.0 0.0
[comp_1.3.1] 0.0 0.0
[sdma0] 0.0 0.0
[vcn_dec] 0.0 0.0
[vcn_enc0] 0.0 0.0
[vcn_enc1] 0.0 0.0
[jpeg_dec] 0.0 0.0
[krfcommd] 0.0 0.0
[kworker/3:3-cgroup_destroy] 0.0 0.0
[kworker/13:0-events] 0.0 0.0
[kworker/9:0-events] 0.0 0.0
[kworker/5:2-events] 0.0 0.0
[kworker/14:1-events] 0.0 0.0
[kworker/6:0-events] 0.0 0.0
[kworker/11:1-events] 0.0 0.0
[kworker/7:3H-kblockd] 0.0 0.0
[kworker/5:1H-ttm] 0.0 0.0
[kworker/2:3H-ttm] 0.0 0.0
[kworker/13:2-mm_percpu_wq] 0.0 0.0
[kworker/u32:5+events_unbound] 0.0 0.2
[kworker/9:3H-ttm] 0.0 0.0
[kworker/7:0H-ttm] 0.0 0.0
[kworker/5:0H-kblockd] 0.0 0.0
[kworker/2:2H-kblockd] 0.0 0.0
[kworker/15:1] 0.0 0.0
./app2 0.0 0.0
[kworker/u32:3-events_unbound] 0.0 0.2
[kworker/3:1H-ttm] 0.0 0.0
[kworker/3:2H-kblockd] 0.0 0.0
./app2 0.0 0.0
[kworker/4:2H-ttm] 0.0 0.0
[kworker/9:0H-ttm] 0.0 0.0
[kworker/4:0H-ttm] 0.0 0.0
[kworker/0:0H-ttm] 0.0 0.0
[kworker/15:0H-ttm] 0.0 0.0
[kworker/1:0H-ttm] 0.0 0.0
[kworker/0:3H-ttm] 0.0 0.0
[kworker/u32:2-events_power_efficient] 0.0 0.3
[kworker/12:2-events] 0.0 0.0
[kworker/3:1-events] 0.0 0.0
[kworker/4:1-events] 0.0 0.0
[kworker/14:2-events] 0.0 0.0
[kworker/15:2H-kblockd] 0.0 0.0
[kworker/1:1H-kblockd] 0.0 0.0
[kworker/8:0-events] 0.0 0.0
[kworker/1:2-events] 0.0 0.0
[kworker/9:2-mm_percpu_wq] 0.0 0.0
[kworker/4:2-events] 0.0 0.0
[kworker/0:1-cgroup_destroy] 0.0 0.0
[kworker/8:1-events] 0.0 0.0
[kworker/6:2-events] 0.0 0.0
[kworker/1:1-events] 0.0 0.0
[kworker/7:2-events] 0.0 0.0
[kworker/10:1-events] 0.0 0.0
[kworker/2:1-mm_percpu_wq] 0.0 0.0
[kworker/12:1-events] 0.0 0.0
[kworker/u32:1-flush-259:0] 0.0 0.1
[kworker/5:1-events] 0.0 0.0
[kworker/15:2-mm_percpu_wq] 0.0 0.0
[kworker/0:0-events] 0.0 0.0
[kworker/2:0H-ttm] 0.0 0.0
[kworker/2:1H-ttm] 0.0 0.0
[kworker/8:0H-ttm] 0.0 0.0
[kworker/8:1H-kblockd] 0.0 0.0
[kworker/9:1H-ttm] 0.0 0.0
[kworker/9:2H-ttm] 0.0 0.0
[kworker/6:9H-ttm] 0.0 0.0
[kworker/10:13H-ttm] 0.0 0.0
[kworker/10:15H-ttm] 0.0 0.0
[kworker/14:5H-ttm] 0.0 0.0
[kworker/14:6H-ttm] 0.0 0.0
[kworker/14:7H-ttm] 0.0 0.0
[kworker/14:8H-kblockd] 0.0 0.0
[kworker/12:8H-ttm] 0.0 0.0
[kworker/12:11H-ttm] 0.0 0.0
[kworker/12:12H-ttm] 0.0 0.0
[kworker/12:15H-kblockd] 0.0 0.0
[kworker/13:5H-ttm] 0.0 0.0
[kworker/4:1H-ttm] 0.0 0.0
[kworker/11:15H-ttm] 0.0 0.0
[kworker/11:16H-kblockd] 0.0 0.0
[kworker/13:9H-ttm] 0.0 0.0
[kworker/6:13H-kblockd] 0.0 0.0
[kworker/6:14H-ttm] 0.0 0.0
[kworker/6:15H-ttm] 0.0 0.0
[kworker/4:3H-ttm] 0.0 0.0
[kworker/11:2-mm_percpu_wq] 0.0 0.0
[kworker/2:3] 0.0 0.0
[kworker/10:2-events] 0.0 0.0
[kworker/5:0-events] 0.0 0.0
[kworker/9:4H] 0.0 0.0
[kworker/u32:0-events_power_efficient] 0.0 0.0
[kworker/u32:4-events_unbound] 0.0 0.1
[kworker/0:1H-ttm] 0.0 0.0
[kworker/0:2H-ttm] 0.0 0.0
[kworker/0:4H] 0.0 0.0
[kworker/14:0-events] 0.0 0.0
[kworker/2:4H] 0.0 0.0

*/