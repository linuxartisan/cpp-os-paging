#include <iostream>
#include "PageTableEntry.h"
#include "Counter.h"
#include "Process.h"
#include "PagingSimulator.h"

using std::cout;

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cout << "Invalid number of arguments!\n";
        cout << "Usage: " << argv[0] << " <input_file>\n";
        return -1;
    }

    /*uint32_t x = 89;
    cout << "x = " << x << '\n';

    PageTableEntry entry(2);
    cout << 'R' << entry.getR() << '\n';
    cout << 'M' << entry.getM() << '\n';
    cout << 'P' << entry.getP() << '\n';

    cout << "setting R to 1...\n";
    entry.setR(true);
    entry.setM(true);
    entry.setP(true);
    cout << 'R' << entry.getR() << '\n';
    cout << 'M' << entry.getM() << '\n';
    cout << 'P' << entry.getP() << '\n';

    // cout << "setting R to 0...\n";
    // entry.setR(false);
    // entry.setM(false);
    // entry.setP(false);
    // cout << 'R' << entry.getR() << '\n';
    // cout << 'M' << entry.getM() << '\n';
    // cout << 'P' << entry.getP() << '\n';

    cout << "page frame number: " << entry.getPageFrameNumber() << '\n';

    entry.setPageFrameNumber(2);
    cout << "page frame number: " << entry.getPageFrameNumber() << '\n';

    entry.setPageFrameNumber(3);
    cout << "page frame number: " << entry.getPageFrameNumber() << '\n';

    // entry.setPageFrameNumber(0);
    // cout << "page frame number: " << entry.getPageFrameNumber() << '\n';

    cout << "\nEntry #2\n";
    PageTableEntry entry2(2);

    cout << "page frame number: " << entry2.getPageFrameNumber() << '\n';

    entry2.setPageFrameNumber(2);
    cout << "page frame number: " << entry2.getPageFrameNumber() << '\n';

    entry2.setPageFrameNumber(1);
    cout << "page frame number: " << entry2.getPageFrameNumber() << '\n';

    // entry2.setPageFrameNumber(0);
    // cout << "page frame number: " << entry2.getPageFrameNumber() << '\n';


    cout << "\nTesting counter\n";

    Counter c;
    cout << c.getValue() << '\n';
    c.insertBitToLeft(1);
    cout << c.getValue() << '\n';
    c.insertBitToLeft(0);
    cout << c.getValue() << '\n';
    c.insertBitToLeft(1);
    cout << c.getValue() << '\n';
    c.insertBitToLeft(1);
    c.insertBitToLeft(1);
    c.insertBitToLeft(1);
    c.insertBitToLeft(1);
    cout << c.getValue() << '\n';

    c.reset();
    cout << c.getValue() << '\n';


    cout << "\nProcess\n";

    Process p1(16, 4);
    p1.printPageTable();
    p1.addPageTableEntry(entry, 0);
    p1.printPageTable();
    p1.addPageTableEntry(entry2, 4);
    p1.printPageTable();
    p1.removePageTableEntry(0);
    p1.printPageTable();

    cout << "\n\nrun()\n";*/
    PagingSimulator sim(argv[1]);
    sim.run();

    return 0;
}
