//Module used to provide access to 6 kernels with two counters at once
// counter/addresser for Convolution 2 layer weight memory read
module conv2_k_mem_read (input logic clk, reset, enable,
                        output logic [7:0] addr0, addr1,
                        output logic done);

    logic [3:0] delay;

    always_ff @(posedge clk or posedge reset) begin
        if (reset == 1'b1) begin
            addr0 <= 8'b00000000;
            addr1 <= 8'b01001011;
            delay <= 4'b0000;
        end
        else if (enable == 1'b1 && done == 1'b0) begin
            if(delay == 4'b0000) begin
                addr0 <= addr0 + 8'b00000001;
                addr1 <= addr1 + 8'b00000001;
            end
            else begin
                delay <= delay + 4'b0001;
            end
        end
    end

    always_comb begin
        if(addr1 == 8'b100101011) begin
            done = 1'b1;
        end
        else begin
            done = 1'b0;
        end
    end
endmodule
