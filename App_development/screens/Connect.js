import { View, Text, Pressable, Image, TextInput } from 'react-native'
import React from 'react'
import COLORS from '../const/colors';
import Button from '../components/Button';

const Connect = () => {
    return(
        <View style={{ flex: 1, marginHorizontal: 22 }}>
            <View style={{ marginVertical: 22 }}>
                <Text style={{
                    fontSize: 22,
                    fontWeight: 'bold',
                    marginVertical: 12,
                    color: COLORS.black
                }}>
                    Link Your Device!
                </Text>
            </View>
            
            {/* network */}
            <View style={{ marginBottom: 20 }}>
                <Text style={{
                    fontSize: 16,
                    fontWeight: 400,
                    marginVertical: 8
                }}>Network Name</Text>

                <View style={{
                    width: "100%",
                    height: 48,
                    borderColor: COLORS.black,
                    borderWidth: 1,
                    borderRadius: 8,
                    alignItems: "center",
                    justifyContent: "center",
                    paddingLeft: 22
                }}>
                    <TextInput
                        placeholder='Enter network name'
                        placeholderTextColor={COLORS.black}
                        //keyboardType='email-address'
                        style={{
                            width: "100%"
                        }}
                    />
                </View>
                
                {/* password */}
                <View style={{ marginBottom: 20 }}>
                    <Text style={{
                        fontSize: 16,
                        fontWeight: 400,
                        marginVertical: 8
                    }}>Password</Text>

                <View style={{
                    width: "100%",
                    height: 48,
                    borderColor: COLORS.black,
                    borderWidth: 1,
                    borderRadius: 8,
                    alignItems: "center",
                    justifyContent: "center",
                    paddingLeft: 22
                }}>
                    <TextInput
                        placeholder='Enter Password'
                        placeholderTextColor={COLORS.black}
                        //keyboardType='email-address'
                        style={{
                            width: "100%"
                        }}
                    />
                </View>
                </View>
            </View>

            <Button
                    title="Connect"
                    filled
                    style={{
                        marginTop: 18,
                        marginBottom: 150,
                    }}
                />

            <View style={{ flexDirection: 'row', alignItems: 'center', marginVertical: 20 }}>
                    <View
                        style={{
                            flex: 1,
                            height: 1,
                            backgroundColor: COLORS.grey,
                            marginHorizontal: 10
                        }}
                    />
                </View>

            <Button
                    title="Find my device"
                    filled
                    style={{
                        marginTop: 1,
                        marginBottom: 4,
                    }}
                />

        </View>
    )
}

export default Connect